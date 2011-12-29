/*
 * =====================================================================================
 *
 *       Filename:  tdb.c
 *
 *    Description:  Test for db
 *
 *        Version:  1.0
 *        Created:  2011年12月27日 20时14分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "sicdbdao.h"
#include "siclog.h"

int main(int argc,char **argv)
{	
//	printf("%d-><-%d\n",sizeof(sic_dbitem),sizeof(sic_dbitem*));
	debugon();
	sic_dbdao *dbdao;
	dbdao=sic_dbdao_init(RAW,".sic/db");
	if(!dbdao)
		return -1;

	sic_dbitem *r;int cou;
	dbdao->query(*(argv+1),&r,&cou);
//	dbdao->query("t");
//	dbdao->clear();
//	dbdao->insert(make_sic_dbitem("风","或","a"));
//	sic_dbitem *p=make_sic_dbitem("风","或","a");
//	dbitem_print(p);
	sic_dbdao_close(dbdao);
//	printf("Fine\n");
	return 0;
}

