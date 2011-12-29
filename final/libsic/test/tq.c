/*
 * =====================================================================================
 *
 *       Filename:  tm.c
 *
 *    Description:  test main
 *
 *        Version:  1.0
 *        Created:  2011年12月29日 21时48分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include "sicmain.h"
#include "siclog.h"

int main(int argc,char **argv)
{
	debugon();
	if(sic_init())
		return -1;
	sic_matchlist(argv[1],"");
	sic_end();
	return 0;
}
