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

int sic_imgopen(char* imgfile,IplImage** img);
int sic_genfeat(IplImage* img,char* featkey);
float sic_compfeat(IplImage* img,char* featkey);

#endif
