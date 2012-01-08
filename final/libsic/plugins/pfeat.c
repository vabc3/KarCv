/*
 * =====================================================================================
 *
 *       Filename:  pfeat.c
 *
 *    Description:  iPfeat
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 22时48分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#include "util.h"
#include "pall.h"
#include "psift.h"
#include "psave.h"
#include "plugins.h"
#include <stdlib.h>

void pfeat_gen(IplImage *img,void **feat)
{
	void *o=NULL;
	sic_plugin_process(PFEATGEN,img,&o);
	*feat=o;
}

static void procgen(void* item,void* input,void **output)
{	
	IplImage *in 	= (IplImage*) input;
	sicpfeat *pf	= (sicpfeat*) item;

	void *tmp;
	pf->generate(in,&tmp);

	*output=(void*)realloc(*output,(pf->index+1)*sizeof(void*));
	
	void **tf;
	tf=(void**)*output;
	*(tf+pf->index)=tmp;
}

void pfeat_save(void *feat,char *fkey)
{
	pfeat_save_arg arg={fkey,feat};
	sic_plugin_process(PFEATSAV,&arg,NULL);
}

static void procsave(void* item,void* input,void **output)
{
	pfeat_save_arg* arg	= (pfeat_save_arg*) input;
	sicpfeat *pf		= (sicpfeat*) item;
	void **p			= (void**)(arg->data);
	void *data			= *(p+pf->index);
	if(pf->save)
		pf->save(data,arg->featkey);
}


void pfeat_load(char *fkey,void **feat)
{
	void *o=NULL;
	sic_log("fkey=%s",fkey);
	sic_plugin_process(PFEATLOD,fkey,&o);
	*feat=o;
}

static void procload(void *item,void* input,void** output)
{
	sicpfeat *pf		= (sicpfeat*) item;
	char *fkey			= (char*) input;
	
	void *tmp;
	if(pf->load)
		pf->load(fkey,&tmp);

	*output=(void*)realloc(*output,(pf->index+1)*sizeof(void*));
	
	void **tf;
	tf=(void**)*output;
	*(tf+pf->index)=tmp;
}

static void proccmp(void*item,void* input,void** output)
{
	sicpfeat *pf        = (sicpfeat*) item;

	void **tf,**f1,**f2;
	
	tf	= (void**)input;
	f1	= (void**)*(tf);
	f2	= (void**)*(tf+1);

	float js,*p;

	js=pf->prop * pf->compare(*(f1+pf->index),*(f2+pf->index));
		
	if(*output==NULL)
		*output=malloc(sizeof(float));

	p=(float*)*output;
	*p+=js;
}

float pfeat_cmp(void *f1,void *f2)
{
	void *o=NULL;

	void** in=(void**)malloc(2*sizeof(void*));

	*in=f1;
	*(in+1)=f2;

	sic_plugin_process(PFEATCMP,in,&o);

	float *p=(float*)o;
	return *p;
}

void pfeat_init()
{
	sic_plugin_regproc(PFEATGEN,procgen);
	sic_plugin_regproc(PFEATSAV,procsave);
	sic_plugin_regproc(PFEATLOD,procload);
	sic_plugin_regproc(PFEATCMP,proccmp);
	sic_plugin_regitem(PFEAT,(void*)&psift);
	sic_plugin_regitem(PFEATGEN|PFEATSAV,(void*)&psave);
}

