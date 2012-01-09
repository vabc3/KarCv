/*
 * =====================================================================================
 *
 *       Filename:  pall.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 23时33分47秒
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

int sic_pall_init()
{
	sic_plugin_init();
	pfix_init();
	pfeat_init();
	pdoc_init();

	return 0;
}

int sic_pall_end()
{
	sic_plugin_end();

	return 0;
}
