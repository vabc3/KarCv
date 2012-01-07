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
#include "pfeat.h"
#include "psift.h"
#include "psave.h"
#include "plugins.h"

void pfeat_run(IplImage *img)
{
	void *o;
	sic_plugin_process(2,img,NULL,&o);
}

void sic_plugin_pgenfeat(void* item,void* input,void* med,void **output)
{	
	IplImage *in 	= (IplImage*) input;
	sicpfeat *pf	= (sicpfeat*)item;
	pf->generate(in,output);
	pf->save(input,NULL);
}

void pfeat_init()
{
	sic_plugin_regproc(2,sic_plugin_pgenfeat);
	sic_plugin_regitem(2,(void*)&psave);
}
