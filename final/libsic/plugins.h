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
	void *item;
	sic_plugin_type type;
	struct sic_plugin_chain_s *next;
}sic_plugin_chain;
typedef void (sic_plugin_proc)(void *,void **);

int sic_plugin_init();
int sic_plugin_end();
int sic_plugin_regproc(const sic_plugin_type type,
		sic_plugin_proc* func);
int sic_plugin_regitem(const sic_plugin_type type,void *item);
int sic_plugin_process(const sic_plugin_type type,void *input,void **output);
#endif
