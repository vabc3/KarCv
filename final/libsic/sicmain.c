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
#include "util.h"
#include "sic.h"
#include "service.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void sic_getver(char *st)
{
	sprintf(st,"%s version %s",PACKAGENAME,SICVERSION);
}

int sic_init(char *dbarg)
{
	sic_log("Sic Init");
	if(srv_dbinit(dbarg)|srv_plugininit())
		return -1;
	return 0;
}

int sic_end()
{
	sic_log("Sic End");
	srv_dbend();
	srv_pluginend();
	return 0;
}

int sic_insert(const char *imgfile,const char *desc)
{
	srv_insertdb(imgfile,desc);
	sic_log("Insert success");
	return srv_general_update();
}

int sic_cleardb()
{
	return srv_cleardb();
}

sic_status* sic_getstatus()
{
	sic_status *rt;
	if(srv_getstatus(&rt))
		return NULL;
	return rt;
}

static void fp(const char *st){
	char buf[255];
	if(!check_imgfile(st,buf))
		srv_insertdb(st,buf);
}

int sic_autoadd(char *dir){
	sic_log("自动添加：%s",dir);
	process_file(dir,fp);	
	return srv_general_update();
}

static int compar(const void *a,const void *b){
	return (((sic_item*)a)->appo<((sic_item*)b)->appo);
}


int sic_matchlist(char *imgfile,char *key,sic_item **si,int topx,char *destfile){
	int n;	
	
	sic_log("Call genlist");

	if(srv_genlist(imgfile,key,si,&n)){
		return -1;
	}
	qsort(*si,n,sizeof(sic_item),compar);

	if((topx>0)&&(n>topx)){
		n=topx;
		*si=realloc(*si,n*sizeof(sic_item));
	}

	if(is_dir(destfile))
		sic_gentex(imgfile,*si,n,destfile);

	return n;
}

void sic_debug()
{
	debugon();
}
