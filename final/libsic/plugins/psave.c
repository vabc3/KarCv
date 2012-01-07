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

#include "plugins.h"
#include "util.h"
#include <cv.h>
#include <highgui.h>
#include "pfeat.h"

static int generate(IplImage *img,void **out)
{
	sic_log("generate in save,%d",img);
	o=(void*)img;
	return 0;
}
 

static int save(void* data,char *fn)
{
	sic_log("Plugin Save,%d",data);
	IplImage* img;
	img	= (IplImage*)(data);
	cvSaveImage("/tmp/test.jpg",img,NULL);
	return 0;
}

sicpfeat psave={
0.9,generate,save,NULL,NULL
};

