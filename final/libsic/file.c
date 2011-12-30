/*
 * =====================================================================================
 *
 *       Filename:  file.c
 *
 *    Description:  File etc
 *
 *        Version:  1.0
 *        Created:  2011年12月30日 15时17分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "sicutil.h"

int is_dir(const char *name)
{
	struct stat st;
	return (stat(name, &st) == 0 && S_ISDIR(st.st_mode));
}

int is_file(const char *name)
{
	struct stat st;
	return ( stat(name, &st) == 0 && S_ISREG(st.st_mode) );
}

int get_dirname(const char *dir,char *dname)
{
	DIR *d=opendir(dir);
	struct dirent *in=readdir(d);
	sic_log("Dir inode=%d",in->d_ino);
	strcpy(dname,in->d_name);
	return 0;
}

static void proc_file(const char *base,char *now,void (*pfunc)(const char *path))
{
	char buf[1024];
	sprintf(buf,"%s/%s",base,now);

	if(is_file(buf)){	
		sic_log("Processing %s",buf);
		pfunc(buf);	
	}else if(is_dir(buf)){
		sic_log("Dir:  %s",buf);

		DIR *d=opendir(buf);
		struct dirent *p,*q=readdir(d);

		while(q){
			p=q;
			if(*(p->d_name)!='.'){
				proc_file(buf,p->d_name,pfunc);
			}
			readdir_r(d,p,&q);
		}
	}
}

int process_file(const char *dir,void (*pfunc)(const char *path))
{
	//FIXME get absolute path
	
	char buf[255],cur[255];
	if(!is_dir(dir))
		return -1;
	getcwd(cur,255);
	chdir(dir);
	getcwd(buf,255);
	chdir(cur);
	sic_log("Base Dir:%s",buf);

	proc_file(buf,".",pfunc);

	return 0;
}

int make_dir(const char *dir)
{	
	if(!is_dir(dir)){
		mkdir(dir,0755);
	}
	return is_dir(dir);
}


int check_imgfile(const char *file,char *desc)
{
	int l=strlen(file),n=0,m=0;
	const char *p;
	if((!is_file(file)||(l<6)))
		return -1;
	if(!strcmp((file+l-4),".jpg")||!strcmp((file+l-4),".png")){
		p=file+l-1;
		while((*p--)!='/')m++;
		while(*p!='/')p--,n++;
		if(n==1){
			p+=n+1;n=m-4;
		}
		strncpy(desc,++p,n);
		*(desc+n)='\0';
//		sic_log("In check desc:%s",desc);
	}else{
		sic_log("Unsupported File");
		return -1;
	}

	return 0;
}

