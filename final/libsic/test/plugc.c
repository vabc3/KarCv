/*
 * =====================================================================================
 *
 *       Filename:  plugc.c
 *
 *    Description:  Plgtest
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 15时08分54秒
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
#include <stdio.h>

void xIp(int a,int **b)
{
	sic_log("xIp called");
	sic_log("%u,%u",&a,b);
	*b=(int*)malloc(sizeof(int));
	**b=a+7;
	sic_log("%d,%d",a,*b);
}
void xp(int a,int **b)
{
	sic_log("xp called");
	sic_log("%u,%u",&a,b);
	*b=(int*)malloc(sizeof(int));
	**b=a*3;
	
	sic_log("%d,%d",a,*b);
}

typedef void (fu)(int,int**);

void pro(void *t,void *i,void **o)
{
	fu* p=(fu*)t;
	int *a=(int*)i;
	sic_log("ia=%x,%x",i,a);
	int *b;
	p(*a,&b);
	*o=b;
	free(a);
}

int main()
{
	debugon();
	int *i;
	i=(int*)malloc(sizeof(int));
	*i=1;
	void *o;
	sic_plugin_init();
	sic_plugin_regitem(1,xp);
	sic_plugin_regitem(1,xIp);
	sic_plugin_regproc(1,pro);
	sic_plugin_process(1,i,&o);
	int *p;
	p=(int*)o;
	printf("%d\n",*p);
	sic_plugin_end();		
	return 0;
}
