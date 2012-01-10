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
	
	IplImage* img;
	char *dir,*prefix,*feat;
	
	void **tf,**f1;
	void* f2;

	tf  	= (void**)input;
	img  	= (IplImage*)*(tf);
	f1		= (void**)*(tf+1);
	f2		= *(f1+pf->index);
	feat  	= (char*)*(tf+2);
	dir		= (char*)*(tf+3);
	prefix	= (char*)*(tf+4);

	char *doc	= (char*)*output;
	char *docx	= pf->gendoc(img,f2,feat,dir,prefix);
	int l		= strlen(doc);
	int lx		= strlen(docx);
	doc			= realloc(doc,l+lx+2);
	strncpy(doc+l,docx,lx+1);
	free(docx);
	*output		= doc;
}

void pdoc_html(IplImage* f1,void* f2,char *feat,char* dir,char* prefix,char** text)
{
	sic_log("base is %s,%s",dir,prefix);
	void *o=(char*)malloc(5);
	strncpy(o,"\0",5);
	void** in=(void**)malloc(5*sizeof(void*));

	*in=f1;
	*(in+1)=f2;
	*(in+2)=feat;
	*(in+3)=dir;
	*(in+4)=prefix;


	sic_plugin_process(PDOC,in,&o);

	*text	= o;
}
