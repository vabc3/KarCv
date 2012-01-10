/*
 * =====================================================================================
 *
 *       Filename:  service.h
 *
 *    Description:  h for service
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 22时37分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#ifndef SIC_SERVICE_H
#define SIC_SERVICE_H	
#include <cv.h>
#include "sic.h"

float sic_compfeat(IplImage* img,char* featkey);

extern int srv_genfeat(IplImage* img,char* featkey);
extern int srv_imgopen(char* imgfile,IplImage** img);
extern int srv_dbinit(char* dbarg);
extern int srv_plugininit();
extern int srv_dbend();
extern int srv_pluginend();
extern int srv_general_update();
extern int srv_insertdb(const char *imgfile,const char *desc);
extern int srv_cleardb();
extern int srv_getstatus(sic_status**);
extern int srv_genlist(char *imgfile,char *key,sic_item **si,int *n);
extern void sic_genhtml(char *img,sic_item *si,int n,char*);

#endif
