/*
 * =====================================================================================
 *
 *       Filename:  tbf.c
 *
 *    Description:  iTest of feature
 *
 *        Version:  1.0
 *        Created:  2011年12月29日 20时02分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include "sicfeat.h"
#include "siclog.h"


int main(int argc,char **argv)
{
	debugon();
	if(argc<4)return -1;
	sic_log("1-%s,2-%s",*(argv+1),*(argv+2));
//	create_featurefile(*(argv+1),*(argv+2));
	int n1,n2;
	s_feature *ft1,*ft2;
	load_feature(*(argv+2),&ft1,&n1);
	load_feature(*(argv+3),&ft2,&n2);
	sic_log("count=%d,%d",n1,n2);
	sic_log("FFt,%lu,%lu",ft1,ft2);
	n1=compare_feature(ft1,n1,ft2,n2);

	sic_log("same=%d",n1);
	return 0;
}

