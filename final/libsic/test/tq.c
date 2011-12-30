/*
 * =====================================================================================
 *
 *       Filename:  tm.c
 *
 *    Description:  图查
 *
 *        Version:  1.0
 *        Created:  2011年12月29日 21时48分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include "sicmain.h"
#include "sicutil.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char **argv)
{
	debugon();
	if(sic_init())
		return -1;
	sic_item *si;
	sic_dbitem *item;
	int i,n;
	sic_matchlist(argv[1],"",&si,&n);
	for(i=0;i<n;i++){
		item = (si+i)->dbitem;
		printf("%d.%.1f%%|%s\t|%s\t|%s\t|\n",i+1,(si+i)->appo,item->imagefile,item->featurefile,item->description);
	}


	free(si);
	sic_end();
	return 0;
}
