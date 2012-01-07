/*
 * =====================================================================================
 *
 *       Filename:  pfeat.h
 *
 *    Description:  Plugin feat
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 22时47分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#ifndef SIC_PFEAT_H
#define SIC_PFEAT_H
#include <cv.h>

typedef struct sic_plugin_feat_s
{
	float prop;
	int (*generate)(IplImage*,void**);
	int (*save)(void*,char*);
	int (*load)(char*);
	float (*compare)(void*);
}sicpfeat;

extern void pfeat_init();
extern void pfeat_run(IplImage *img);

#endif
