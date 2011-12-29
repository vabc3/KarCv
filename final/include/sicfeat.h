/*
 * =====================================================================================
 *
 *       Filename:  sicfeat.h
 *
 *    Description:  warpper
 *
 *        Version:  1.0
 *        Created:  2011年12月29日 19时35分02秒
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
int genfeature(char *imgfile,s_feature **feature,int *n);
int create_featurefile(char *imgfile,char *featurefile);
int load_feature(char *featurefile,s_feature **feature,int *n);
int save_feature(char *featurefile,s_feature *feature,int n);
int compare_feature(s_feature *f1,int n1,s_feature *f2,int n2);


