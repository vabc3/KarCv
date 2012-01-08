/*
 * =====================================================================================
 *
 *       Filename:  psift.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年01月08日 00时14分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#include "imgfeatures.h"
typedef struct feature s_feature;
typedef struct siftf
{
	int n;
	s_feature* feat;
}sic_sift;

extern sicpfeat psift;
