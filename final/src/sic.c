/*
 * =====================================================================================
 *
 *       Filename:  sic.c
 *
 *    Description:  Main Entrance 
 *
 *        Version:  1.0
 *        Created:  2011年12月27日 22时23分57秒
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
#include "sicdb.h"

static void status();

int main(){
	debugon();
	sic_log("---Main---");
	sic_init();
	status();
	sic_end();
	return 0;
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
