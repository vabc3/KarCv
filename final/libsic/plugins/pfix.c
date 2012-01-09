/*
 * =====================================================================================
 *
 *       Filename:  pfix.c
 *
 *    Description:  Fix Impl
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 23时25分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include "pall.h"
#include "plugins.h"
#include "util.h"

#define MAXW	800

typedef void (procpfix)(IplImage *in,IplImage **out);

static void sic_foo(IplImage*in,IplImage**out)
{
	sic_log("foo0");
//	cvLine(in,cvPoint(0,3),cvPoint(20,80),CV_RGB(0,0,255),1,CV_AA,0);
	*out=in;
}

static void resize(IplImage* in,IplImage**out)
{
	sic_log("Resize");
	CvSize ds;
	int wd	= in->width;

	if(wd>MAXW){
		ds.width	= MAXW;
		ds.height	= in->height * MAXW /wd;
		*out		= cvCreateImage( ds, in->depth, in->nChannels);
		cvResize(in,*out,CV_INTER_LINEAR);
		cvReleaseImage(&in);
	}else{
		*out=in;
	}
}

static void sic_plugin_pfix(void* item,void* input,void** output);

void pfix_init()
{
	sic_plugin_regproc(PFIX,sic_plugin_pfix);
	sic_plugin_regitem(PFIX,sic_foo);
	sic_plugin_regitem(PFIX,resize);
}

void pfix_img(IplImage *in,IplImage **out)
{
	void *o;
	o=NULL;
	sic_plugin_process(PFIX,in,&o);
	*out=(IplImage*)o;
}

static void sic_plugin_pfix(void* item,void* input,void** output)
{
	procpfix *pf	= (procpfix*)item;
	IplImage *in;
	if(*output==NULL)
		in	= (IplImage*)input;
	else
		in 	= (IplImage*)(*output);
	IplImage *ou;
	pf(in,&ou);
	*output			= (void*)ou;
}

