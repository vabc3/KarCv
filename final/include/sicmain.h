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
int sic_init();
int sic_end();
int sic_status();
int sic_insert(char *imgfile,char *desc);
int sic_cleardb();
int sic_autoadd(char *dir);
int sic_match(char *imgfile,char *key);
int sic_matchlist(char *imgfile,char *key);
#endif
