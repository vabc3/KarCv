/*
 * =====================================================================================
 *
 *       Filename:  file.c
 *
 *    Description:  File util test
 *
 *        Version:  1.0
 *        Created:  2011年12月30日 15时11分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include <assert.h>
#include "sicutil.h"
#include "sicmain.h"

const static char dname[]="Diii";
int pc=0;
void fp(const char *st){
//	sic_log("-->%s",st);
	char buf[255];

	if(!check_imgfile(st,buf)){
		sic_log("Desc:%s",buf);
		if(!sic_insert(st,buf))pc++;
	}
}

int main(int argc,char **argv)
{
	debugon();
	assert(make_dir(dname)==1);
	assert(is_dir(dname)==1);
	assert(is_file(dname)==0);
	assert(is_file(argv[0])==1);
	sic_init();
	process_file(argv[1],fp);
	sic_end();
	sic_log("%d file(s) proceed",pc);
	return 0;
}
