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
#include "featproc.h"
#include <cv.h>
#include <highgui.h>
void sic_plugin_savepic(void** const data)
{
	sic_log("Plugin Save");
	IplImage* img;
	img	= (IplImage*)(*data);
	cvSaveImage("/tmp/test.jpg",img,NULL);
}
