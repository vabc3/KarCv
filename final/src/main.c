/*
 * =====================================================================================
 *
 *       Filename:  sic.c
 *
 *    Description:  Main Entrance 
 *
 *        Version:  1.0
 *        Created:  2011年12月27日 22时23分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include "func.h"
#include "arg.h"

int main(int argc,char **argv){
	
	parse_opt(argc,argv);
	docmd();

	return 0;
}

