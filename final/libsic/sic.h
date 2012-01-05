/*
 * =====================================================================================
 *
 *       Filename:  sicmain.h
 *
 *    Description:  Main 
 *
 *        Version:  1.0
 *        Created:  2011年12月29日 21时40分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#ifndef SIC_H
#define SIC_H


#ifdef __cplusplus
extern "C" {
#endif


#define PACKAGENAME	"libsic"
#define SICVERSION "0.1.1"

#define STRMLEN 128

/*-----------------------------------------------------------------------------
 * item struct definition 
 *-----------------------------------------------------------------------------*/

typedef struct sic_item_s{
    char imagefile[STRMLEN];        //image path
    char description[STRMLEN];      //description
	float appo;
} sic_item;

typedef struct sic_status_s{
//TODO add status
	int count;
}sic_status;

extern void sic_getver(char *st);
extern int sic_init(char *dbarg);
extern int sic_end();
extern int sic_cleardb();
extern sic_status* sic_getstatus();
extern int sic_insert(const char *imgfile,const char *desc);
extern int sic_autoadd(char *dir);
extern int sic_matchlist(char *imgfile,char *key,sic_item** const,int topx) __attribute__((warn_unused_result));
extern void sic_debug();

#ifdef __cplusplus
}
#endif

#endif
