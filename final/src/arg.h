/*
 * =====================================================================================
 *
 *       Filename:  arg.h
 *
 *    Description:  argument h
 *
 *        Version:  1.0
 *        Created:  2011年12月30日 19时22分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#define N 70
typedef enum cmds_s{
	Cundef,Cversion,Cstatus,Cclear,Cinsert,Cimport,Cmatch
}cmds;

typedef struct opt_s{
	cmds cmd;
	int debug;
	char img[N];
	char key[N];
	char dir[N];
	int showlist;
}sic_opt;


sic_opt* parse_opt(int argc,char **argv);
