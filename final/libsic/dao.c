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
#include <string.h>
#include "util.h"
#include "dao.h"
#include "dao_sqlite3.h"



void dbitems_print(sic_dbitem** const items,const int count)
{
	int i;
	sic_log("---%d结果打印开始---",count);
	for(i=0;i<count;i++){
		dbitem_print(*items+i);
	}
	sic_log("---%d结果打印结束---",count);
}

void dbitem_print(const sic_dbitem *item)
{
	sic_log("|%s-%s-%s\t|",item->imagefile,item->featurefile,item->description);
}

inline int make_sic_dbitem(sic_dbitem *p,const char *imagefile,
						const char *featurefile,const char * description)
{
	strcpy(p->imagefile,imagefile);	
	strcpy(p->featurefile,featurefile);
	strcpy(p->description,description);
	return 0;
}

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
			dbdao->clear	= sic_sqlite3_clear;
			dbdao->save		= sic_sqlite3_save;
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

