/*
 * =====================================================================================
 *
 *       Filename:  tm.c
 *
 *    Description:  test 插入
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
#include "sicutil.h"

int main()
{
	debugon();
	if(sic_init())
		return -1;
	sic_insert("qq2.jpg","tx");
//	sic_cleardb();
	sic_end();
	return 0;
}
