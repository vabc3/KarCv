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
#ifndef SICUTIL_H
#define SICUTIL_H 
#define sic_log(fmt...) sic_log_f(__FILE__, __LINE__, fmt)

extern void debugon();
extern void sic_log_f(const char *filename,const unsigned int,const char *fmt,...);

extern int is_dir(const char *name);
extern int is_file(const char *name);
extern int get_dirname(const char *dir,char *dname);
extern int process_file(const char *dir,void (*pfunc)(const char *path));
extern int make_dir(const char *dir);
extern int check_imgfile(const char *file,char *desc);

#endif
