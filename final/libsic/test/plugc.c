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
#include "../plugins.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

void xIp(void** const tr)
{
	sic_log("xIp called");
	int *t =(int*)tr;
	(*t)*=2;
}
void xp(void** const tr)
{
	sic_log("xp called");
	int *t =(int*)tr;
	*t=*t+2;
}

int main()
{
	debugon();
	int r=1;
	sic_plugin_init();
	sic_plugin_reg(1,xIp);
	sic_plugin_reg(1,xp);
	sic_plugin_process(1,&r);
	printf("%d\n",r);
	sic_plugin_end();		
	return 0;
}
