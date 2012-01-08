/*
 * =====================================================================================
 *
 *       Filename:  save_pic.c
 *
 *    Description:  Save proceeded pic
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 16时21分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include "plugins.h"
#include "util.h"
#include "pall.h"

static int generate(IplImage *img,void **out)
{
	sic_log("generate in save,%d",img);
	*out=(void*)img;
	return 0;
}

static int save(void* data,char* fn)
{
	sic_log("save in save,%d(%s)",data,fn);
	IplImage* img;
	char buf[512];
	sprintf(buf,"%s.jpg",fn);
	img	= (IplImage*)(data);
	show("x",img);
	cvSaveImage(buf,img,NULL);
	return 0;
}

sicpfeat psave={
0,0.5,generate,save,NULL,NULL
};

