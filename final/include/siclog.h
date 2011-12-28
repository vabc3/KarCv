/*
 * =====================================================================================
 *
 *       Filename:  siclog.h
 *
 *    Description:  Log for sic
 *
 *        Version:  1.0
 *        Created:  2011年12月28日 13时49分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#ifndef SICLOG_H
#define SICLOG_H 
#define sic_log(fmt...) sic_log_f(__FILE__, __LINE__, fmt)

extern int debug;
extern void debugon();
extern void sic_log_f(const char *filename,const int ling,const char *fmt,...);

#endif
