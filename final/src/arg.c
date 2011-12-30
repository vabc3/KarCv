/*
 * =====================================================================================
 *
 *       Filename:  arg.c
 *
 *    Description:  Arguments
 *
 *        Version:  1.0
 *        Created:  2011年12月30日 18时54分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "arg.h"
#include "sicutil.h"

static struct option lop[] ={
	{"debug"	, 0, 0, 'd'},
	{"version"	, 0, 0, 'v'},
	{"status"	, 0, 0, 's'},
	{"clear"	, 0, 0, 'c'},
	{"insert"	, 0, 0, 'i'},
	{"import"	, 0, 0, 'p'},
	{"match"	, 0, 0, 'm'},
	{"list"		, 0, 0, 'l'},
	{0,0,0,0}
};
static char sop[]="dvsci:p:m:l";

static void argdump(sic_opt *p)
{
	sic_log("debug=%d,list=%d",p->debug,p->showlist);
	sic_log("cmd=%d",p->cmd);
	sic_log("dir=%s,img=%s,key=%s",p->dir,p->img,p->key);
}


sic_opt* parse_opt(int argc,char **argv)
{
	sic_opt *o;
	o=(sic_opt*)malloc(sizeof(sic_opt));
	strcpy(o->dir,"a");
	strcpy(o->img,"b");
	strcpy(o->key,"c");


	int c;
	do{
		c= getopt_long(argc,argv,sop,lop,NULL);

		switch(c){
			case 'd':
				o->debug=1;
				break;
			case 'v':
				o->cmd=Cversion;
				break;
			case 's':
				o->cmd=Cstatus;
				break;
			case 'c':
				o->cmd=Cclear;
				break;
			case 'i':
				o->cmd=Cinsert;
				break;
			case 'p':
				o->cmd=Cimport;
				break;
			case 'm':
				o->cmd=Cmatch;
				break;
			case 'l':
				o->showlist=1;
				break;
			default:
				free(o);
				return NULL;
		}
	}while (c!=-1);
	argdump(o);
	return o;
}
