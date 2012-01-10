/*
 * =====================================================================================
 *
 *       Filename:  pdoc.c
 *
 *    Description:  iPdoc
 *
 *        Version:  1.0
 *        Created:  2012年01月09日 23时21分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include "pall.h"
#include "util.h"
#include "plugins.h"

static void procdoc(void*item,void* input,void** output);

void pdoc_init()
{
	sic_plugin_regproc(PDOC,procdoc);
}

static void procdoc(void*item,void* input,void** output)
{
	
	sicpfeat *pf        = (sicpfeat*) item;

	void **tf,**f1,**f2;
	char *ba;

	tf  = (void**)input;
	f1  = (void**)*(tf);
	f2  = (void**)*(tf+1);
	ba	= (char*)*(tf+2);

	char *doc	= (char*)*output;
	char *docx	= pf->gendoc(*(f1+pf->index),*(f2+pf->index),ba);
	int l		= strlen(doc);
	int lx		= strlen(docx);
	doc			= realloc(doc,l+lx+2);
	strncpy(doc+l,docx,lx+1);
	free(docx);
	*output		= doc;
}

void pdoc_html(void* f1,void* f2,char* base,char** text)
{
	sic_log("base is %s",base);
	void *o=(char*)malloc(5);
	strncpy(o,"\0",5);
	void** in=(void**)malloc(3*sizeof(void*));
	*in=f1;
	*(in+1)=f2;

	*(in+2)=base;

	sic_plugin_process(PDOC,in,&o);

	*text	= o;
}
