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
#include "siclog.h"
#include "sicdb.h"
#include "sicdbdao.h"

static sqlite3 *db;
static int count;

const static char DB_CREATE[]="create table if not exists sicdb("
							"id integer primary key autoincrement,"
							"imagefile varchar(255),"
							"featurefile varchar(255),"
							"description varchar(255))";
const static char DB_CLEAR[]="delete from sicdb";
const static char DB_INSERT[]="insert into sicdb (imagefile,featurefile,description)"
								"values('%s','%s','%s')";
const static char DB_QUERY[]="select * from sicdb where description like '%%%s%%'";


int sic_sqlite3_open(const char *arg){
	
	sic_log("Open Called,Arg:%s",arg);
	
	if(sqlite3_open(arg,&db)){
		sic_log("DB_err:%s",sqlite3_errmsg(db));
		return -1;
	}

	sic_log("Open ok,Querying Table");

	sqlite3_exec(db,DB_CREATE,NULL,NULL,NULL);
	
	//sic_log("Result:%s,%d.",msg,rt);
	
	if(sqlite3_exec(db,"select * from sicdb",NULL,NULL,NULL)){
		sic_log("Failed");
		return -1;
	}

	sic_log("Table OK!");

	return 0;
}

int sic_sqlite3_close(){
	sic_log("Close Called");
	return sqlite3_close(db);
}

int sic_sqlite3_clear(){
	sic_log("清库");
	if(sqlite3_exec(db,DB_CLEAR,NULL,NULL,NULL))
		return -1;
	return 0;
}

int sic_sqlite3_insert(sic_dbitem* item)
{
	char buf[512];
	sic_log("Insert Called");
	if(!item)
		return -1;
	sprintf(buf,DB_INSERT,item->imagefile,item->featurefile,item->description);
	sqlite3_exec(db,buf,NULL,NULL,NULL);
	return 0;
}

static int query_cb(void *a,int b, char **c,char **d)
{
	sic_log("回调被呼叫 id=%s",*c);
	sic_log("a=%lu",a);
	count++;
	sic_dbitem **q = a;
//	int rs=count*sizeof(sic_dbitem*);
//	sic_log("%d",rs);
	*q=(sic_dbitem*)realloc(*q,count*sizeof(sic_dbitem*));
//	*q=p;
	sic_dbitem *qq=*q+count-1;
	sic_log("%lu>%lu",*q,qq);
//	*(*q+count-1)=p;
//	make_sic_dbitem(&qq,*(c+1),*(c+2),*(c+3));

	dbitem_print((*q+count-1));
	return 0;
}

int sic_sqlite3_query(const char *key,sic_dbitem **its,int *cou)
{	
	char buf[512];
	sic_log("查询[%s]",key);
	sprintf(buf,DB_QUERY,key);
	
	sic_log("its=%lu",its);
	*its=NULL;count=0;
	sqlite3_exec(db,buf,query_cb,its,NULL);
	sic_log("共%d个结果",count);
	*cou=count;

	int i;
	sic_dbitem *p;
	for(i=0;i<count;i++){
		p=*its+i;
		sic_log("%lu",p);
		dbitem_print(p);
	}
	return 0;
}

