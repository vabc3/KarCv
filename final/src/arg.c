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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "arg.h"

static struct option lop[] ={
	{"debug", 	no_argument, 		0, 'd'},
	{"version",	no_argument, 		0, 'v'},
	{"status", 	no_argument, 		0, 's'},
	{"clear",	no_argument, 		0, 'c'},
	{"insert",	no_argument,	 	0, 'i'},
	{"import",	no_argument, 		0, 'o'},
	{"match",	no_argument,	 	0, 'm'},
	{"list",	no_argument, 		0, 'l'},
	{"path",	required_argument,	0, 'p'},
	{"key",		required_argument,	0, 'k'},
	{"help",	no_argument,		0, 'h'},
	{"dbdir",	no_argument,		0, 'b'},
	{"topn",	required_argument,	0, 'n'},
	{0,0,0,0}
};
static char sop[]="dvsciomlp:k:hbn";

/*
static void argdump(sic_opt *p)
{
	printf("debug=%d,list=%d\n",p->debug,p->showlist);
	printf("cmd=%d\n",p->cmd);
	printf("dirimg=%s,key=%s\n",p->path,p->key);
}
*/

inline static void setcmd(cmds cmd)
{
	if(op.cmd==Cundef)
		op.cmd=cmd;
	else
		op.cmd=Cmulti;
}

void parse_opt(int argc,char **argv)
{
	int c;
	op.cmd		=Cundef;
	op.debug	= 0;
	op.dbarg	= getenv("HOME");
	op.path		= NULL;
	op.key		= NULL;
	op.showlist	= 0;
	do{
		c= getopt_long(argc,argv,sop,lop,NULL);

		switch(c){
			case 'd':
				op.debug=1;
				break;
			case 'v':
				setcmd(Cversion);
				break;
			case 's':
				setcmd(Cstatus);
				break;
			case 'c':
				setcmd(Cclear);
				break;
			case 'i':
				setcmd(Cinsert);
				break;
			case 'o':
				setcmd(Cimport);
				break;
			case 'm':
				setcmd(Cmatch);
				break;
			case 'l':
				op.showlist=1;
				break;
			case 'p':
				op.path=optarg;
				break;
			case 'k':
				op.key=optarg;
				break;
			case 'h':
				setcmd(Chelp);
			case 'b':
				op.dbarg=optarg;
			default:
				break;
		}
	}while (c!=-1);
//	argdump(&op);
}
