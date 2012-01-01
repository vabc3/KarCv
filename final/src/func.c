/*
 * =====================================================================================
 *
 *       Filename:  func.c
 *
 *    Description:  Functions
 *
 *        Version:  1.0
 *        Created:  2011年12月30日 18时55分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sic.h>
#include "arg.h"

extern sic_opt op;
static void debug();
static void version();
static void usage();
static void status();
static void clear();
static void insert();
static void import();
static void match();


void docmd()
{
	if(op.debug)
		debug();
	sic_init();
	switch(op.cmd){
		case Cversion:
			version();
			break;
		case Cstatus:
			status();
			break;
		case Cclear:
			clear();
			break;
		case Cinsert:
			insert();
			break;
		case Cimport:
			import();
			break;
		case Cmatch:
			match();
			break;
		case Chelp:
		case Cundef:
			usage();
			break;
	}
	sic_end();
}

static void printt(char *it,char *desc){
	printf("%-30s%s\n",it,desc);
}

void debug()
{
	sic_debug();	
}

void usage()
{
	printf("Usage:sic [OPTION] <COMMAND [OPTION]>\n"
			"Options:\n"
		  );
	printt("-d/--debug","Enbable verbose debug logging");
	printf("\nAvailable commands:\n");
	printt("version","Show ver info");
	printt("status","Show database status");
	printt("clear","Clean database");
	printt("insert <img> <key>","Insert an record");
	printt("import <dir>","Import an dir");
	printt("match <img> [key]","Find match record");
	printf("\nOptions for match:\n");
	printt("-l/--list","show the entire list");
}

void version()
{
	char buf[255];
	sic_getver(buf);
	printf("%s\n",buf);
}

void status()
{
	sic_dbitem *its,*item;
	int i,n;

	if(sic_status(&its,&n))
		return;

	printf("现有%d条记录\n",n);
	for(i=0;i<n;i++){
		item = its+i;
		printf("%s\t|%s\t|%s\t|\n",item->imagefile,item->featurefile,item->description);
	}

	free(its);
}

void clear()
{
	sic_cleardb();
}

void insert()
{
	if(!op.key){
		printf("key must be set.\n");
		return;
	}
	if(!op.path){
		printf("Path must be set.\n");
		return;
	}
	sic_insert(op.path,op.key);
}

void import()
{
	if(!op.path){
		printf("Path must be set.\n");
		return;
	}
	printf("%d files Added.\n",sic_autoadd(op.path));
}

void match()
{
	sic_item *si;
	sic_dbitem *item;
	int i,n;
	if(!op.path){
		printf("Path must be set.\n");
		return;
	}
	if(!op.key){
		sic_matchlist(op.path,"",&si,&n);
	}else
		sic_matchlist(op.path,op.key,&si,&n);

	for(i=0;i<n;i++){
		item = (si+i)->dbitem;
		printf("%d. %.2f%%|%s\t|%s\t|\n",i+1,(si+i)->appo,item->description,item->imagefile);
	}

}
