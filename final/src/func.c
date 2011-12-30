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
#include "sicutil.h"
#include "sicmain.h"

static void printt(char *it,char *desc){
	printf("%-30s%s\n",it,desc);
}

void debug()
{
	debugon();	
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

