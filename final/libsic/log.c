/*
 * =====================================================================================
 *
 *       Filename:  siclog.c
 *
 *    Description:  Log impl
 *
 *        Version:  1.0
 *        Created:  2011年12月28日 13时51分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdarg.h>
#include "sicutil.h"

static int debug=0;

void debugon()
{
	debug=1;
}


void sic_log_f(const char *filename,const unsigned int line,const char *fmt,...)
{
	char buf[255];
	char *pb;
	if(debug){
		va_list ap;
		sprintf(buf, "[%s:%u]\t", filename, line);
		pb=buf;
		while(*pb++);
//		while(*pb++){fprintf(stderr,"%c",*pb);}
//		printf("{}%d{}",pb-buf);
		if(pb-buf<15){
			*(pb-1)='\t';
			*(pb)='\0';
		}
		fprintf(stderr,"%s", buf);
		va_start(ap, fmt);
		vfprintf(stderr,fmt, ap);
		va_end(ap);
		fprintf(stderr,"\n");
	}
}
