/*
 * =====================================================================================
 *
 *       Filename:  sicdbdao.h
 *
 *    Description:  Headfile for db access method
 *
 *        Version:  1.0
 *        Created:  2011年12月27日 20时05分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#ifndef SICDBDAO_H
#define SICDBDAO_H

#include "sicdb.h"

typedef enum sic_dbtype_e{
	SQLITE3,
	RAW
} sic_dbtype;

struct sic_dbdao_s{
	sic_dbtype dbtype;
	int (*connect)(const char *args);
	int (*close)();
	int (*insert)(sic_dbitem* item);
	sic_dbitem* (*query)(int id);
};

typedef struct sic_dbdao_s sic_dbdao;

extern sic_dbdao* sic_dbdao_init(sic_dbtype dbtype,const char *arg);
extern void sic_dbdao_close(sic_dbdao *dao);

#endif
