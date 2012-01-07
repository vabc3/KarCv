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

typedef enum sic_plugin_type_s
{
	PREPROC,FEATPROC
}sic_plugin_type;

typedef struct sic_plugin_chain_s
{
	void (*proc)(void** const data);
	sic_plugin_type type;//0->filter 1->procedure
	struct sic_plugin_chain_s *next;
}sic_plugin_chain;

extern int sic_plugin_init();
extern int sic_plugin_end();
extern int sic_plugin_reg(const sic_plugin_type type,void (*func)(void** const));
extern int sic_plugin_process(const sic_plugin_type type,void *data);
#endif
