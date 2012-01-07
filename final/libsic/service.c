/*
 * =====================================================================================
 *
 *       Filename:  service.c
 *
 *    Description:  Service
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 22时36分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include <highgui.h>
#include "service.h"
#include "util.h"
#include "plugins/pall.h"

int sic_imgopen(char* imgfile,IplImage** img)
{
	if(!imgfile){
		sic_log("name NULL");
		return -1;
	}
	sic_log("Srv Opening:%s",imgfile);
	*img = cvLoadImage( imgfile, 1 );
	if(!*img){
		sic_log("Img error");
		return -1;
	}
	IplImage *out;

	pfix_run(*img,&out);
	*img	= out;
	show("r",*img);
	cvWaitKey(0);
	return 0;
}

int sic_genfeat(IplImage* img,char* featkey)
{
	pfeat_run(img);
	return 0;	
}
