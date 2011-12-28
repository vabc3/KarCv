/*
 * =====================================================================================
 *
 *       Filename:  sicdbdao.c
 *
 *    Description:  Impl
 *
 *        Version:  1.0
 *        Created:  2011年12月27日 20时44分24秒
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
#include "siclog.h"
#include "sicdbdao.h"
#include "sicdbdao_sqlite3.h"

sic_dbdao* sic_dbdao_init(sic_dbtype dbtype,const char *arg)
{
	sic_log("Init called,Type:%d",dbtype);
	sic_dbdao* dbdao 	= (sic_dbdao*)malloc(sizeof(sic_dbdao));
	dbdao->dbtype		= dbtype;
	switch (dbtype){
		case RAW:
		case SQLITE3:
		default:
			dbdao->connect	= sic_sqlite3_open;
			dbdao->close	= sic_sqlite3_close;
			dbdao->insert	= sic_sqlite3_insert;
			dbdao->query	= sic_sqlite3_query;
	}
	int rt=dbdao->connect(arg);
	if(rt!=0){
		sic_log("DB error:%d",rt);
		free(dbdao);
		dbdao=NULL;
	}
	return dbdao;
}

void sic_dbdao_close(sic_dbdao *dao)
{
	dao->close();
	free(dao);
}

