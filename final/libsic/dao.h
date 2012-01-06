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
#define STRMLEN 128
typedef struct sic_dbitem_s{
	int id;							//ider
	char imagefile[STRMLEN];        //image path
	char featurefile[STRMLEN];      //feature file path
	char description[STRMLEN];      //description
} sic_dbitem;


typedef enum sic_dbtype_e{
	SQLITE3,
	RAW
} sic_dbtype;

struct sic_dbdao_s{
	sic_dbtype dbtype;
	int (*connect)(const char *args);
	int (*close)();
	int (*clear)();
	int (*save)(const sic_dbitem* item);
	int (*query)(const char *key,sic_dbitem** const its,int *count);
};

typedef struct sic_dbdao_s sic_dbdao;

extern inline int make_sic_dbitem(sic_dbitem *item,const char *imagefile,
		const char *featurefile,const char * description);
extern void dbitems_print(sic_dbitem **const,const int count);
extern void dbitem_print(const sic_dbitem*);
extern sic_dbdao* sic_dbdao_init(sic_dbtype dbtype,const char *arg);
extern void sic_dbdao_close(sic_dbdao *dao);

#endif
