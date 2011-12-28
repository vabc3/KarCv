/*
 * =====================================================================================
 *
 *       Filename:  sicdb.h
 *
 *    Description:  Head File for feature database
 *
 *        Version:  1.0
 *        Created:  2011年12月27日 19时56分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#ifndef SICDB_H
#define SICDB_H

#define STRMLEN	255

/*-----------------------------------------------------------------------------
 * item struct definition 
 *-----------------------------------------------------------------------------*/
struct sic_dbitem_s{
	char imagefile[STRMLEN];		//image path
	char featurefile[STRMLEN];		//feature file path
	char description[STRMLEN];		//description
};

typedef struct sic_dbitem_s sic_dbitem;

#endif
