/*
 * =====================================================================================
 *
 *       Filename:  tdb.c
 *
 *    Description:  测数据库
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
	debugon();
	sic_dbdao *dbdao;
	dbdao=sic_dbdao_init(RAW,".sic/db");
	if(!dbdao)
		return -1;

	sic_dbitem *r;int cou;
	dbdao->query(*(argv+1),&r,&cou);
	
	sic_dbdao_close(dbdao);
	return 0;
}

