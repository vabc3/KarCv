/*
 * =====================================================================================
 *
 *       Filename:  plugins.c
 *
 *    Description:  Plugin  impl
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 15时23分04秒
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
#include <stdlib.h>

static sic_plugin_chain* head;
static sic_plugin_chain* tail;
sic_plugin_proc* funcs[4];

int sic_plugin_init()
{
	sic_log("***PLUGIN INIT***");
	head		= malloc(sizeof(sic_plugin_chain));
	tail		= malloc(sizeof(sic_plugin_chain));
	head->next	= tail;
	tail->next	= NULL;
	return 0;
}

int sic_plugin_end()
{
	sic_log("***PLUGIN ENDD***");
	sic_plugin_chain *p,*q;
	p	= head;
	while(p){
		q	= p;
		p	= p->next;
		free(q);
	}
	return 0;
}

int sic_plugin_regitem(const sic_plugin_type type,void *item)
{
	sic_plugin_chain* p;
	p		= malloc(sizeof(sic_plugin_chain));
	p->type	= type;
	p->item	= item;
	p->next	= head->next;
	head->next = p;
	return 0;
}

int sic_plugin_regproc(const sic_plugin_type type,sic_plugin_proc* func)
{
	sic_log("***PLUGIN REGPROC***");
	funcs[type]=func;
	return 0;
}

int sic_plugin_process(const sic_plugin_type type,void *input,void **output)
{
	sic_log("***PLUGIN PROC{%d}***",type);
	sic_plugin_chain* p;
	p 	= head->next;
	while(p!=tail){
		if(type==p->type){
			funcs[type](input,output);
		}
		p	= p->next;
	}
	return 0;
}
