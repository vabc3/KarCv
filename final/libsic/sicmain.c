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
#include "sicdbdao.h"
#include "sicfeat.h"
#include "sicutil.h"
#include "sic.h"
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static sic_dbdao* dao=NULL;
static char fnbuf[255];

void sic_getver(char *st)
{
	sprintf(st,"%s version %s",PACKAGENAME,SICVERSION);
}

static void filename_gen(){
	struct timeval tmv;
	gettimeofday(&tmv,NULL);
	sprintf(fnbuf,".sic/si%lu.%lu.ft",tmv.tv_sec,tmv.tv_usec);
}

int sic_init()
{
	sic_log("Sic Init");
	make_dir(".sic");
	dao=sic_dbdao_init(SQLITE3,".sic/db");
	if(!dao)
		return -1;
	return 0;
}

int sic_end()
{
	sic_log("Sic End");
	sic_dbdao_close(dao);
	return 0;
}

int sic_insert(const char *imgfile,const char *desc)
{
	if(!dao){
		sic_log("Not inited");
		return -1;
	}
	sic_dbitem *item=(sic_dbitem*)calloc(1,sizeof(sic_dbitem));
	sic_log("Ins %s(%s)",imgfile,desc);
	filename_gen();
	sic_log("%s",fnbuf);
	if(create_featurefile(imgfile,fnbuf)){
		return -1;
	}
	make_sic_dbitem(item,imgfile,fnbuf,desc);
//	strcpy(item.imagefile,imgfile);
//	strcpy(item.featurefile,fnbuf);
//	strcpy(item.description,desc);
	if(dao->insert(item)){
		return -1;
	}
	free(item);
	sic_log("Insert success");
	return 0;
}
	
int sic_cleardb()
{
	if(!dao){
		sic_log("Not inited");
		return -1;
	}
	return dao->clear();
}

int sic_status(sic_dbitem **its,int *n)
{
	if(!dao){
		sic_log("Not inited");
		return -1;
	}
	dao->query("",its,n);

	return 0;
}
static int pc;
static void fp(const char *st){
	char buf[255];

	if(!check_imgfile(st,buf)){
		sic_log("Desc:%s",buf);
		if(!sic_insert(st,buf))pc++;
	}
}


int sic_autoadd(char *dir){
	if(!dao){
		sic_log("Not inited");
		return -1;
	}
	sic_log("自动添加：%s",dir);
	pc=0;
	process_file(dir,fp);	
	return pc;
}

static int compar(const void *a,const void *b){
	return (((sic_item*)a)->appo<((sic_item*)b)->appo);
}

static int genlist(char *imgfile,char *key,sic_item **si,int *n){
	s_feature *base_f,*each_f;
	int nb,nf,cou,i,ne;
	sic_dbitem *its;
	
	sic_log("列表");
	genfeature(imgfile,&base_f,&nb);
	nf=compare_feature(base_f,nb,base_f,nb);
	dao->query(key,&its,&cou);
	
	nf=compare_feature(base_f,nb,base_f,nb);
	*si=(sic_item*)malloc(cou*sizeof(sic_item));
	
	for(i=0;i<cou;i++){
		(*si+i)->dbitem	= its+i;
		load_feature((its+i)->featurefile,&each_f,&ne);
		(*si+i)->appo	= 100.0 * compare_feature(base_f,nb,each_f,ne) / nf ;
	}
	*n=cou;
	free(base_f);

	return 0;
}

int sic_matchlist(char *imgfile,char *key,sic_item **si,int *n){
	
	if(!dao){
		sic_log("Not inited");
		return -1;
	}
	sic_log("Call genlist");
	genlist(imgfile,key,si,n);
	qsort(*si,*n,sizeof(sic_item),compar);

	return 0;
}

void sic_debug()
{
	debugon();
}
