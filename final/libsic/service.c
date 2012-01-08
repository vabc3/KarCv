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
	for(i=0;i<n;i++){
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

	return count;

}

int srv_insertdb(const char *imgfile,const char *desc)
{
	char tmp[STRMLEN];
	sic_log("Ins %s(%s)",imgfile,desc);
	realpath(imgfile,tmp);
	sic_dbitem item;
	make_sic_dbitem(&item,-1,tmp,"",desc);
	if(dao->save(&item)){
		return -1;
	}
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

	for(i=0;i<cou;i++){
		strncpy((*si+i)->imagefile,(its+i)->imagefile,STRMLEN);
		strncpy((*si+i)->description,(its+i)->description,STRMLEN);
		sprintf(ff,"%s/%s",dbdir,(its+i)->featurefile);
		pfeat_load(ff,&each_f);
		(*si+i)->appo   = pfeat_cmp(base_f,each_f)*100;
		free(each_f);
	}
	*n=cou;
	free(base_f);
	free(its);
	
	return 0;
}
