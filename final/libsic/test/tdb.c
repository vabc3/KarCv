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
#include "dao.h"
#include "util.h"

int main(int argc,char **argv)
{	
	debugon();
	sic_dbdao *dbdao;
	dbdao=sic_dbdao_init(RAW,"/home/rquiss/.sic/db");
	if(!dbdao)
		return -1;

	sic_dbitem r;

	make_sic_dbitem(&r,16,"x","y","");
	dbdao->save(&r);
	dbdao->delete(14);
	sic_dbdao_close(dbdao);
	return 0;
}

