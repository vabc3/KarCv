/*
 * =====================================================================================
 *
 *       Filename:  sicdbdao_sqlite3.h
 *
 *    Description:  Head file for sq3
 *
 *        Version:  1.0
 *        Created:  2011年12月28日 15时18分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#ifndef SICDBDAO_SQLITE3_H
#define SICDBDAO_SQLITE3_H
extern int sic_sqlite3_open(const char *arg);
extern int sic_sqlite3_close();
extern int sic_sqlite3_save(const sic_dbitem* item);
extern int sic_sqlite3_query(const char *key,sic_dbitem** const its,int *count);
extern int sic_sqlite3_clear();
#endif
