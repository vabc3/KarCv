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
#include <stdlib.h>
#include "util.h"

static void ftfile_delete(const char *path);

int is_dir(const char *name)
{
	if(!name)return 0;
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
//		sic_log("Processing %s",buf);
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
		closedir(d);
	}
}

int process_file(const char *dir,void (*pfunc)(const char *path))
{
	char *buf;
	buf=realpath(dir,NULL);
	sic_log("Base Dir:%s",buf);

	proc_file(buf,".",pfunc);

	free(buf);

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

void dir_ftclean(const char *dir,const char *prefix)
{
	sic_log("ftclean:%s",dir);
	if(!is_dir(dir))
		return;
	DIR *d=opendir(dir);
	struct dirent *p,*q=readdir(d);
	char buf[255];

	int len=strlen(prefix);
	while(q){
		p=q;
//		sic_log("Delete Search File:%s",p->d_name);
		if(!strncmp(p->d_name,prefix,len)){
			sprintf(buf,"%s/%s",dir,p->d_name);
//			sic_log("Delete Confirm File:%s",buf);
			ftfile_delete(buf);
		}
		readdir_r(d,p,&q);
	}
	closedir(d);
}

static void ftfile_delete(const char *path)
{
	if(!is_file(path))
		return;
	sic_log("Delete File:%s",path);
	unlink(path);
}
