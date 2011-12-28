/*
 * =====================================================================================
 *
 *       Filename:  sicdbdao_sqlite3.c
 *
 *    Description:  Sqlite3 impl
 *
 *        Version:  1.0
 *        Created:  2011年12月28日 15时11分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <sqlite3.h>
#include "siclog.h"
#include "sicdb.h"

static sqlite3 *db;

static char DB_CREATE[]="create table sicdb(id int,"
							"imagefile varchar(255),"
							"featurefile varchar(255),"
							"description varchar(255))";

int sic_sqlite3_open(const char *arg){
	int rt;
	sic_log("Open Called,Arg:%s",arg);
	rt = sqlite3_open(arg,&db);
	if (rt){
		sic_log("DB_err:%s",sqlite3_errmsg(db));
		return rt;
	}

	sic_log("Open ok,Querying Table");
	char *msg;
	rt=sqlite3_exec(db,"select * from sicdb",NULL,NULL,&msg);
	//		sic_log("Result:%s,%d.",msg,rt);
	
	if(rt){
		sic_log("No such table... Creating");
		rt=sqlite3_exec(db,DB_CREATE,NULL,NULL,&msg);
	}
	
	if(rt){
		sic_log("Failed");
	}

	sic_log("Table OK!");

	return 0;
}

int sic_sqlite3_close(){
	sic_log("Close Called");
	return sqlite3_close(db);
}

int sic_sqlite3_insert(sic_dbitem* item)
{
	sic_log("Insert Called");
	return 0;
}

sic_dbitem* sic_sqlite3_query(int id)
{
	sic_log("Query Called for %d",id);
	return 0;
}

