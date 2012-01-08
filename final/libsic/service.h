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

int sic_imgopen(char* imgfile,IplImage** img);
int sic_genfeat(IplImage* img,char* featkey);
float sic_compfeat(IplImage* img,char* featkey);

int srv_dbinit(char* dbarg);
int srv_plugininit();
int srv_dbend();
int srv_pluginend();
int srv_general_update();
int srv_insertdb(const char *imgfile,const char *desc);
int srv_cleardb();
int srv_getstatus(sic_status**);
int srv_genlist(char *imgfile,char *key,sic_item **si,int *n);

#endif
