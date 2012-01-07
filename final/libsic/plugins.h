/*
 * =====================================================================================
 *
 *       Filename:  plugins.h
 *
 *    Description:  Rplugin
 *
 *        Version:  1.0
 *        Created:  2012年01月06日 23时07分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#ifndef SIC_PLUGIN_H
#define SIC_PLUGIN_H
typedef struct sic_plugin_chain_s
{
	void (*proc)(void** const data);
	int type;//0->filter 1->procedure
	struct sic_plugin_chain_s *next;
}sic_plugin_chain;

int sic_plugin_init();
int sic_plugin_end();
int sic_plugin_reg(const int type,void (*func)(void** const));
int sic_plugin_process(const int type,void *data);
#endif
