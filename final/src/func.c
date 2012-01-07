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
#include "func.h"

static void debug();
static void version();
static void usage();
static void status();
static void clear();
static void insert();
static void import();
static void match();
static void nocmdmsg();
static void multicmdmsg();

static void nocmdmsg()
{
	printf("Must specify a command. --help for help\n");
	exit(-1);
}

static void multicmdmsg()
{
	printf("Only can use one command at one time\n");
	exit(-1);
}

void docmd()
{
	if(op.debug)
		debug();
	sic_init(op.dbarg);
	switch(op.cmd){
		case Cmulti:
			multicmdmsg();
			break;
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
		case Cundef:
			nocmdmsg();
			break;
		case Chelp:
		default:
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
	printt("-v/--version","Show ver info");
	printt("-s/--status","Show database status");
	printt("-c/--clear","Clean database");
	printt("-i/--insert","Insert an record");
	printt("-o/--import","Import an dir");
	printt("-m/--match","Find match record");
	printf("\nOptions for commands:\n");
	printt("-b/--dbdir <db>","Speicfy the db dir(default to ~/.sic/)");
	printt("-k/--key <key>","Give the key");
	printt("-p/--path <path>","Specify the dir/file path");
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
//	int i,n;
	sic_status* st = sic_getstatus();
	if(st){
		printf("现有%d条记录\n",st->count),free(st);
	}
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
	if(sic_insert(op.path,op.key)){
		printf("Insert error.\n");
	}
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
	int i,n;
	if(!op.path){
		printf("Path must be set.\n");
		return;
	}
	if(!op.key){
		n=sic_matchlist(op.path,"",&si,-1,NULL);
	}else
		n=sic_matchlist(op.path,op.key,&si,-1,NULL);
	if(n<0){
		printf("Image error!\n");
	}
	for(i=0;i<n;i++){
		printf("%d. %.2f%%|%s\t|%s\t|\n",i+1,(si+i)->appo,(si+i)->description,(si+i)->imagefile);
	}
//	printf("Before free\n");
	free(si);
}
