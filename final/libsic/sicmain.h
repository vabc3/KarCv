/*
 * =====================================================================================
 *
 *       Filename:  sicmain.h
 *
 *    Description:  Main 
 *
 *        Version:  1.0
 *        Created:  2011年12月29日 21时40分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#ifndef SICMAIN_H
#define SICMAIN_H
#include <sicdb.h>

typedef struct sic_item_s{
	    sic_dbitem *dbitem;
		    float appo;
} sic_item;

int sic_init();
int sic_end();
int sic_cleardb();
int sic_status(sic_dbitem **its,int *n);
int sic_insert(const char *imgfile,const char *desc);
int sic_autoadd(char *dir);
int sic_matchlist(char *imgfile,char *key,sic_item**,int*);
#endif
