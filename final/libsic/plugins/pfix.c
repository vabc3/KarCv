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

#include "pfix.h"
#include "plugins.h"
static void sic_foo(IplImage*,IplImage**);
static void sic_foo2(IplImage*in,IplImage**out)
{
	cvLine(in,cvPoint(70,3),cvPoint(20,80),CV_RGB(0,0,255),1,CV_AA,0);
	*out=in;
}

void pfix_init()
{
	sic_plugin_regproc(1,sic_plugin_pfix);
	sic_plugin_regitem(1,sic_foo);
	sic_plugin_regitem(1,sic_foo2);
}

void pfix_run(IplImage *in,IplImage **out)
{
	void *o;
	sic_plugin_process(1,NULL,in,&o);
	*out=(IplImage*)o;
}

void sic_plugin_pfix(void* item,void* input,void *med,void** output)
{
	procpfix *pf	= (procpfix*)item;
	IplImage *in	= (IplImage*)med;
	IplImage *ou;
	pf(in,&ou);
	*output			= (void*)ou;
}

void sic_foo(IplImage *in,IplImage **out)
{
	cvLine(in,cvPoint(0,3),cvPoint(20,80),CV_RGB(0,0,255),1,CV_AA,0);
	*out=in;
}
