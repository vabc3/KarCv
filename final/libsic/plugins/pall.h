/*
 * =====================================================================================
 *
 *       Filename:  pall.h
 *
 *    Description:  All collect
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 23时24分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#ifndef SIC_PALL_H
#define SIC_PALL_H
#include <cv.h>
#include <stdio.h>

#define PFIX		1
#define PFEATGEN	(1<<1)
#define PFEATSAV	(1<<2)
#define PFEATLOD	(1<<3)
#define PFEATCMP	(1<<4)
#define PDOC		(1<<5)
#define PFEAT		(PFEATGEN|PFEATSAV|PFEATLOD|PFEATCMP|PDOC)

extern int sic_pall_init();
extern int sic_pall_end();

typedef struct sic_plugin_feat_s
{
	int index;
	float prop;
	int (*generate)(IplImage*,void**);
	int (*save)(void*,char*);
	int (*load)(char*,void**);
	float (*compare)(void*,void*);
	char* (*gendoc)(IplImage*,void*,char*,char*,char*);
}sicpfeat;


typedef struct pfeat_save_arg_s
{
	char* featkey;
	void* data;
}pfeat_save_arg;


extern void pfeat_init();
extern void pfeat_gen(IplImage *img,void**);
extern void pfeat_save(void *feat,char *fkey);
extern void pfeat_load(char *fkey,void **feat);
extern float pfeat_cmp(void *f1,void *f2);


extern void pfix_init();
extern void pfix_img(IplImage *in,IplImage **out);

extern void pdoc_init();
extern void pdoc_html(IplImage*,void*,char* fe,char*dir,char*pf,FILE *fp);

#endif
