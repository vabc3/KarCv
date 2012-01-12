/*
 * =====================================================================================
 *
 *       Filename:  service.c
 *
 *    Description:  Service
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 22时36分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include <highgui.h>
#include <stdio.h>
#include "service.h"
#include "util.h"
#include "plugins/pall.h"
#include "dao.h"

int srv_imgopen(char* imgfile,IplImage** img)
{
	if(!imgfile){
		sic_log("name NULL");
		return -1;
	}
	sic_log("Srv Opening:%s",imgfile);
	*img = cvLoadImage( imgfile, 1 );
	if(!*img){
		sic_log("Img error");
		return -1;
	}
	IplImage *out;

	pfix_img(*img,&out);
	*img	= out;
	//	show("r",*img);
	//	cvWaitKey(0);
	return 0;
}

int srv_genfeat(IplImage* img,char* featkey)
{
	void *feat;
	pfeat_gen(img,&feat);
	pfeat_save(feat,featkey);
	return 0;	
}


static const char dirfile[]         = ".sic";
static const char ftprefix[]        = "ft";
static const char sqlite3_dbfile[]  = "db";
static sic_dbdao* dao               = NULL;
static char dbdir[255],fnbuf[255];

int srv_dbinit(char* dbarg)
{
	char dw[STRMLEN];
	if(!dbarg){
		strcpy(dw,getenv("HOME"));
	}else{
		strncpy(dw,dbarg,255);
	}

	sprintf(dbdir,"%s/%s",dw,dirfile);
	make_dir(dbdir);
	sprintf(fnbuf,"%s/%s",dbdir,sqlite3_dbfile);
	dao=sic_dbdao_init(SQLITE3,fnbuf);
	if(!dao)
		return -1;
	return 0;
}

int srv_plugininit()
{
	return sic_pall_init();
}

int srv_dbend()
{
	sic_dbdao_close(dao);
	return 0;
}

int srv_pluginend()
{
	return sic_pall_end();
}

int srv_general_update()
{
	sic_dbitem *q,*p;
	int n,i,count;
	char fnbuf[STRMLEN];
	char ebuf[255];

	sic_log("Gener_update");
	dao->query(NULL,&q,&n);
	sic_log("Found %d items for update.",n);
	count=n;
	sic_process_begin(n);
	for(i=0;i<n;i++){
		sic_process_call(i,"update");
		sic_log("Item id:%d",(q+i)->id);
		sprintf(fnbuf,"%s%d",ftprefix,(q+i)->id);
		sic_log("%s",fnbuf);
		sprintf(ebuf,"%s/%s",dbdir,fnbuf);
		IplImage *img;
		if(srv_imgopen((q+i)->imagefile,&img)){
			dao->delete((q+i)->id);
			count--;
		}else{
			srv_genfeat(img,ebuf);
			strncpy((q+i)->featurefile,fnbuf,STRMLEN);
			dao->save((q+i));
		}
	}
	sic_process_end();

	return count;

}

int srv_insertdb(const char *imgfile,const char *desc)
{
	sic_log("Ins %s(%s)",imgfile,desc);
	char *tmp;
	tmp=realpath(imgfile,NULL);
	
	sic_dbitem item;
	make_sic_dbitem(&item,-1,tmp,"",desc);
	if(dao->save(&item)){
		return -1;
	}
	free(tmp);
	return 0;

}

int srv_cleardb()
{
	dir_ftclean(dbdir,ftprefix);
	return dao->clear();
}

int srv_getstatus(sic_status** sts)
{
	sic_dbitem *its;
	int n;
	dao->query("",&its,&n);
	free(its);

	sic_status *rt = (sic_status*)malloc(sizeof(sic_status));
	rt->count=n;
	*sts=rt;
	return 0;
}

int srv_genlist(char *imgfile,char *key,sic_item **si,int *n)
{
	void *base_f,*each_f;
	int cou,i,ne;

	sic_dbitem* its;
	sic_log("列表");

	IplImage *img;
	if(srv_imgopen(imgfile,&img)){
		return -1;
	}
	pfeat_gen(img,&base_f);

	dao->query(key,&its,&cou);

	*si=(sic_item*)malloc(cou*sizeof(sic_item));

	char ff[STRMLEN];

	sic_process_begin(cou);
	for(i=0;i<cou;i++){
		sic_process_call(i,"x");
		strncpy((*si+i)->imagefile,(its+i)->imagefile,STRMLEN);
		strncpy((*si+i)->feat,(its+i)->featurefile,STRMLEN);
		strncpy((*si+i)->description,(its+i)->description,STRMLEN);
		sprintf(ff,"%s/%s",dbdir,(its+i)->featurefile);
		pfeat_load(ff,&each_f);
		(*si+i)->appo   = pfeat_cmp(base_f,each_f)*100;
		free(each_f);
	}
	sic_process_end();
	*n=cou;
	free(base_f);
	free(its);

	return 0;
}


void sic_genhtml(char *imgfile,sic_item *si,int n,char *base)
{
	sic_log("Gen html Called [%s]",base);
	void *ef;
	IplImage *img;
	if(srv_imgopen(imgfile,&img)){
		return;
	}
	pfeat_gen(img,&ef);

	int i;
	char ff[STRMLEN];
	char fn[]="index.htm";
	char hn[255];
	sprintf(hn,"%s/%s",base,fn);
	FILE* fp=fopen(hn,"w");
	char bp[255];

	fprintf(fp,"<h3>图像文件:%s</h3>\n",imgfile);
	fprintf(fp,"<img src=\"%s\"/>\n",imgfile);
	for(i=0;i<n;i++){
		fprintf(fp,"<p>%d.[%.2f%%],%s,%s</p>\n",i+1,
				(si+i)->appo,(si+i)->description,(si+i)->imagefile);
		
		sic_log((si+i)->feat);
		sprintf(ff,"%s/%s",dbdir,(si+i)->feat);
		fprintf(fp,"<img src=\"%s.jpg\"/>\n",ff);
		sprintf(bp,"im%d",i+1);
		pdoc_html(img,ef,ff,base,bp,fp);
	}
	fclose(fp);
}

void sic_gentex(char *imgfile,sic_item *si,int n,char *base)
{
	sic_log("Gen tex Called [%s]",base);
	void *ef;
	IplImage *img;
	if(srv_imgopen(imgfile,&img)){
		return;
	}
	pfeat_gen(img,&ef);

	int i;
	char ff[STRMLEN];
	char fn[]="index.tex";
	char hn[255];
	sprintf(hn,"%s/%s",base,fn);
	FILE* fp=fopen(hn,"a+");
	char bp[255];

	fprintf(fp,"\\subsection{图像文件:%s}\n",imgfile);
	fprintf(fp,"\\includegraphics[width=15cm,angle=0]{%s}\n\n",imgfile);
	for(i=0;i<n;i++){
		fprintf(fp,"\\paragraph{%d}\n",i+1);
		fprintf(fp,"[%.2f\\%%],%s,%s\n\n",
				(si+i)->appo,(si+i)->description,(si+i)->imagefile);
		
		sic_log((si+i)->feat);
		sprintf(ff,"%s/%s",dbdir,(si+i)->feat);
//		fprintf(fp,"\\centering\\includegraphics[width=15cm,angle=0]{%s.jpg}\n\n",ff);
		sprintf(bp,"im%d",i+1);
		pdoc_tex(img,ef,ff,base,bp,fp);
		if(i%2==0)fprintf(fp,"\\clearpage\n");
	}
	fclose(fp);
}

