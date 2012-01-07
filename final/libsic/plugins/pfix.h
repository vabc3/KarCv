/*
 * =====================================================================================
 *
 *       Filename:  pfix.h
 *
 *    Description:  Pre process fix
 *
 *        Version:  1.0
 *        Created:  2012年01月07日 23时22分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#ifndef SIC_PFIX_H
#define SIC_PFIX_H
#include <cv.h>
typedef void (procpfix)(IplImage *in,IplImage **out);

extern void sic_plugin_pfix(void*,void*,void*,void**);
extern void pfix_init();
extern void pfix_run(IplImage *in,IplImage **out);
#endif


