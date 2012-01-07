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
#include <stdlib.h>
#include <sqlite3.h>
#include "util.h"
#include "dao.h"
#include "dao_sqlite3.h"

static sqlite3*	db;
static int 		count;

static const char DB_CREATE[]	= "create table if not exists sicdb("
								"id integer primary key autoincrement,"
								"imagefile varchar(255),"
								"featurefile varchar(255),"
								"description varchar(255))";
static const char DB_CLEAR[]	= "delete from sicdb";
static const char DB_INSERT[]	= "insert into sicdb"
								"(imagefile,featurefile,description)"
								"values('%s','%s','%s')";
static const char DB_UPDATE[]	= "update sicdb set featurefile='%s' where id='%d'";
static const char DB_KQUERY[]	= "select * from sicdb where description like '%%%s%%'";
static const char DB_NQUERY[]	= "select * from sicdb where featurefile=''";
static const char DB_DELETE[]	= "delete from sicdb where id='%d'";

//static int query_cb(void *a,int b, char **c,char **d);

int sic_sqlite3_open(const char *arg){
	
	sic_log("Open Database,Arg:%s",arg);
	
	if(sqlite3_open(arg,&db)){
		sic_log("DB_err:%s",sqlite3_errmsg(db));
		return -1;
	}

	sqlite3_exec(db,DB_CREATE,NULL,NULL,NULL);
	
	if(sqlite3_exec(db,"select * from sicdb",NULL,NULL,NULL)){
		sic_log("Failed");
		return -1;
	}

	return 0;
}

int sic_sqlite3_close(){
	sic_log("Close database");
	return sqlite3_close(db);
}

int sic_sqlite3_clear(){
	sic_log("清库");
	if(sqlite3_exec(db,DB_CLEAR,NULL,NULL,NULL))
		return -1;
	return 0;
}

int sic_sqlite3_save(const sic_dbitem* item)
{
	char buf[512];
	if(!item)
		return -1;
	if(item->id<0){
//		sic_log("Insert Called");
		sprintf(buf,DB_INSERT,item->imagefile,item->featurefile,item->description);
	}else{
//		sic_log("Update Called");
		sprintf(buf,DB_UPDATE,item->featurefile,item->id);
	}
	sqlite3_exec(db,buf,NULL,NULL,NULL);

	return 0;
}

static int query_cb(void *a,int b, char **c,char **d)
{
	count++;
	sic_dbitem **q = a;
	
	*q=(sic_dbitem*)realloc(*q,count*sizeof(sic_dbitem));
	make_sic_dbitem(*q+count-1,atoi(*c),*(c+1),*(c+2),*(c+3));

	return 0;
}

int sic_sqlite3_query(const char *key,sic_dbitem** const its,int *cou)
{	
	char buf[512];
	sic_log("查询[%s]",key);
	if(key)
		sprintf(buf,DB_KQUERY,key);
	else
		sprintf(buf,DB_NQUERY);
	

	*its=NULL;
	count=0;

	sqlite3_exec(db,buf,query_cb,its,NULL);
	sic_log("共%d个结果",count);
	*cou=count;
	
	dbitems_print(its,*cou);
	
	return 0;
}

int sic_sqlite3_delete(int id)
{
	char buf[512];
	sic_log("Delete id->%d",id);
	sprintf(buf,DB_DELETE,id);
    sqlite3_exec(db,buf,NULL,NULL,NULL);

	return 0;
}
