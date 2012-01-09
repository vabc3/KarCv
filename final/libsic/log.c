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
#include "util.h"

static int debug=0;
static int proc=1;
static int pc;
static int la;

void debugon()
{
	debug=1;
	proc=0;
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

void sic_process_begin(int n)
{

	if(proc){
		pc=n;la=0;
		printf("Processing...(  0,%3d)",pc);
	}
}

void sic_process_call(int i,char *s)
{
	if(proc){
		char buf[255];
		sprintf(buf,"\033[%dD(%%3d/%%3d) %%s",la+10);
		la=strlen(s);
		printf(buf,i,pc,s);
		//	printf("\033[9D(%3d/%3d)%s",i,pc,s);
		fflush(stdout);
	}
}

void sic_process_end()
{
	char buf[255];
	sprintf(buf,"\033[%dDDone!        \n",la+10);
	if(proc){
		printf("\033[9DDone!        \n");
	}
}

