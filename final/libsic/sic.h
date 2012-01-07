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
#define SICVERSION "0.1.2"

#define STRMLEN 256

/*-----------------------------------------------------------------------------
 * item struct definition 
 *-----------------------------------------------------------------------------*/

typedef struct sic_item_s			//返回信息结构
{
    char 	imagefile[STRMLEN];		//image path
    char 	description[STRMLEN];	//description
	float	appo;					//相似度
} sic_item;

typedef struct sic_status_s			//状态信息结构 
{
//TODO add status
	int count;
}sic_status;

extern void sic_getver(char *st);	//获取库文件版本号
extern sic_status* sic_getstatus();	//获取库状态信息
extern int sic_init(char *dbarg);	//初始化
extern int sic_end();				//终止化收尾工作
extern int sic_cleardb();			//清除库
extern int sic_insert(const char *imgfile,const char *desc);	//插入单条数据
extern int sic_autoadd(char *dir);								//自动扫描目录入库
extern int sic_matchlist(char *imgfile,char *key,sic_item** const,
		int topx,char *destfile)__attribute__((warn_unused_result));//返回查询结果
extern void sic_debug();			//打开debug模式

#ifdef __cplusplus
}
#endif

#endif
