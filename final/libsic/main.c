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
#include "siclog.h"
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sic_item_s{
	sic_dbitem *dbitem;
	float appo;
} sic_item;

static sic_dbdao* dao;
static char fnbuf[255];

static void filename_gen(){
	struct timeval tmv;
	gettimeofday(&tmv,NULL);
	sprintf(fnbuf,".sic/si%lu.%lu.ft",tmv.tv_sec,tmv.tv_usec);
}

int sic_init()
{
	sic_log("Sic Init");
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

int sic_insert(char *imgfile,char *desc)
{
	sic_dbitem item;
	sic_log("Ins %s(%s)",imgfile,desc);
	filename_gen();
	sic_log("%s",fnbuf);
	if(create_featurefile(imgfile,fnbuf)){
		return -1;
	}
	strcpy(item.imagefile,imgfile);
	strcpy(item.featurefile,fnbuf);
	strcpy(item.description,desc);
	if(!(dao->insert(&item))){
		return -1;
	}

	return 0;
}
	
int sic_cleardb()
{
	return dao->clear();
}

int sic_status()
{
	sic_dbitem *its,*item;
	int i,n;
	dao->query("",&its,&n);

	printf("现有%d条记录\n",n);
	for(i=0;i<n;i++){
		item = its+i;
		printf("%s\t|%s\t|%s\t|\n",item->imagefile,item->featurefile,item->description);
	}

	free(its);
	return 0;
}

int sic_autoadd(char *dir){
	//TODO
	return -1;
}

static sic_item *si;



int compar(const void *a,const void *b){
	return (((sic_item*)a)->appo<((sic_item*)b)->appo);
}

static int genlist(char *imgfile,char *key,int *n){
	s_feature *base_f,*each_f;
	int nb,nf,cou,i,ne;
	sic_dbitem *its;
	
	sic_log("列表");
	genfeature(imgfile,&base_f,&nb);
	nf=compare_feature(base_f,nb,base_f,nb);
	dao->query(key,&its,&cou);
	
	nf=compare_feature(base_f,nb,base_f,nb);
	si=(sic_item*)malloc(cou*sizeof(sic_item));
	
	for(i=0;i<cou;i++){
		(si+i)->dbitem	= its+i;
		load_feature((its+i)->featurefile,&each_f,&ne);
		(si+i)->appo	= 100.0 * compare_feature(each_f,ne,base_f,nb) / nf ;
	}
	*n=cou;
	free(base_f);

	return 0;
}

int  sic_match(char *imgfile,char *key){
	return -2;
}

int sic_matchlist(char *imgfile,char *key){
	int i,n;
	sic_log("Call genlist");
	genlist(imgfile,key,&n);
	qsort(si,n,sizeof(sic_item),compar);

	sic_dbitem *item;

	for(i=0;i<n;i++){
		item = (si+i)->dbitem;
		printf("%d.%.1f%%|%s\t|%s\t|%s\t|\n",i+1,(si+i)->appo,item->imagefile,item->featurefile,item->description);
	}
	
	free(si);

	return 0;
}

