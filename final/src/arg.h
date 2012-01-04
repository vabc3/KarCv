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
#ifndef ARG_H
#define ARG_H
#define N 70

typedef enum cmds_s{
	Cversion,Cstatus,Cclear,Cinsert,Cimport,Cmatch,Chelp,Cmulti,Cundef
}cmds;

typedef struct opt_s{
	cmds cmd;
	int debug;
	char *path;
	char *key;
	char *dbarg;
	int showlist;
}sic_opt;

extern sic_opt op;

void parse_opt(int argc,char **argv);

#endif
