/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main for sic
 *
 *        Version:  1.0
 *        Created:  2011年12月29日 21时38分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#include "dao.h"
#include "feat.h"
#include "util.h"
#include "sic.h"
#include "plugins.h"
#include "plugins/proc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char dirfile[]			= ".sic";
static const char ftprefix[]		= "ft";
static const char sqlite3_dbfile[]	= "db";
static sic_dbdao* dao				= NULL;
static char fnbuf[255],dbdir[255];

void sic_getver(char *st)
{
	sprintf(st,"%s version %s",PACKAGENAME,SICVERSION);
}

int sic_init(char *dbarg)
{
	sic_log("Sic Init");

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

	sic_plugin_init();
	sic_plugin_reg(FEATPROC,sic_plugin_savepic);

	return 0;
}

int sic_end()
{
	sic_log("Sic End");
	sic_plugin_end();
	sic_dbdao_close(dao);
	return 0;
}

static int general_update()
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
		sprintf(fnbuf,"%s%d.sift",ftprefix,(q+i)->id);
		sic_log("%s",fnbuf);
		sprintf(ebuf,"%s/%s",dbdir,fnbuf);
		if(create_featurefile((q+i)->imagefile,ebuf)){
			dao->delete((q+i)->id);
			count--;
		}else{
			strncpy((q+i)->featurefile,fnbuf,STRMLEN);
			dao->save((q+i));
		}
	}

	return count;
}

static int insertdb(const char *imgfile,const char *desc)
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

int sic_insert(const char *imgfile,const char *desc)
{
	if(!dao){
		sic_log("Not inited");
		return -1;
	}
	insertdb(imgfile,desc);
	sic_log("Insert success");
	return general_update();
}

int sic_cleardb()
{
	if(!dao){
		sic_log("Not inited");
		return -1;
	}

	dir_ftclean(dbdir,ftprefix);
	return dao->clear();
}

sic_status* sic_getstatus()
{
	if(!dao)return -1;
	
	sic_dbitem *its;
	int n;
	dao->query("",&its,&n);
	free(its);
	
	sic_status *rt = (sic_status*)malloc(sizeof(sic_status));
	rt->count=n;
	return rt;
}

static void fp(const char *st){
	char buf[255];

	if(!check_imgfile(st,buf)){
		sic_log("Desc:%s",buf);
		insertdb(st,buf);
	}
}

int sic_autoadd(char *dir){
	if(!dao)return -1;
	
	sic_log("自动添加：%s",dir);
	process_file(dir,fp);	
	return general_update();
}

static int compar(const void *a,const void *b){
	return (((sic_item*)a)->appo<((sic_item*)b)->appo);
}

static int genlist(char *imgfile,char *key,sic_item **si,int *n){
	s_feature *base_f,*each_f;
	int nb,nf,cou,i,ne;
	
	sic_dbitem* its;
	sic_log("列表");

	if(genfeature(imgfile,&base_f,&nb)){
		return -1;
	}
	
	nf=compare_feature(base_f,nb,base_f,nb);
	dao->query(key,&its,&cou);
	
	nf=compare_feature(base_f,nb,base_f,nb);
	*si=(sic_item*)malloc(cou*sizeof(sic_item));

	char ff[STRMLEN];

	for(i=0;i<cou;i++){
		strncpy((*si+i)->imagefile,(its+i)->imagefile,STRMLEN);
		strncpy((*si+i)->description,(its+i)->description,STRMLEN);
		sprintf(ff,"%s/%s",dbdir,(its+i)->featurefile);
		load_feature(ff,&each_f,&ne);
		(*si+i)->appo	=(float) 100.0 * compare_feature(base_f,nb,each_f,ne) / nf ;
		free(each_f);
	}
	*n=cou;
	free(base_f);
	free(its);
	return 0;
}

int sic_matchlist(char *imgfile,char *key,sic_item **si,int topx,char *destfile){
	int n;	
	if(!dao){
		sic_log("Not inited");
		return -1;
	}
	sic_log("Call genlist");

	if(genlist(imgfile,key,si,&n)){
		return -1;
	}
	qsort(*si,n,sizeof(sic_item),compar);

	if((topx>0)&&(n>topx)){
		n=topx;
		*si=realloc(*si,n*sizeof(sic_item));
	}

	return n;
}

void sic_debug()
{
	debugon();
}


