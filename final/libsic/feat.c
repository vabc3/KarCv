/*
 * =====================================================================================
 *
 *       Filename:  feat.c
 *
 *    Description:  featl
 *
 *        Version:  1.0
 *        Created:  2011年12月29日 19时43分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */

#include <cv.h>
#include <highgui.h>
#include "util.h"
#include "sift.h"
#include "kdtree.h"
#include "feat.h"
#include "plugins.h"

int intvls = SIFT_INTVLS;
double sigma = SIFT_SIGMA;
double contr_thr = SIFT_CONTR_THR;
int curv_thr = SIFT_CURV_THR;
int img_dbl = SIFT_IMG_DBL;
int descr_width = SIFT_DESCR_WIDTH;
int descr_hist_bins = SIFT_DESCR_HIST_BINS;

int genfeature(const char *imgfile,s_feature **feature,int *n)
{
	IplImage *img;

	if(!imgfile){
		sic_log("name NULL");
		return -1;
	}
	sic_log("Gen Feature:%s",imgfile);
	img = cvLoadImage( imgfile, 1 );
	if(!img){
		sic_log("Img error");
		return -1;
	}
	*n = _sift_features( img, feature, intvls, sigma, contr_thr, curv_thr,
			img_dbl, descr_width, descr_hist_bins );

	sic_plugin_process(1,&img);

	cvReleaseImage(&img);
	return 0;
}

s_feature *fe;

int create_featurefile(const char *imgfile,const char *featurefile){
	int n;
	if(genfeature(imgfile,&fe,&n))
		return -1;
	save_feature(featurefile,fe,n);
	free(fe);
	return 0;
}

int load_feature(char *featurefile,s_feature **feature,int *n)
{
	struct feature* feat=NULL;

	if(!featurefile){
		sic_log("name NULL");
		return -1;
	}
	sic_log("LoadFeatFrom:%s",featurefile);
	*n = import_features( featurefile, FEATURE_LOWE, &feat );
	if(*n==-1){
		*feature=NULL;
		sic_log("Feat import error");
		return -1;
	}
	*feature=feat;
	return 0;
}

int save_feature(const char *featurefile,s_feature *feature,int n)
{
	sic_log("SaveFeatTo:%s",featurefile);
	export_features(featurefile,feature,n);
	return 0;
}

/* the maximum number of keypoint NN candidates to check during BBF search */
#define KDTREE_BBF_MAX_NN_CHKS 200
  
/* threshold on squared ratio of distances between NN and 2nd NN */
#define NN_SQ_DIST_RATIO_THR 0.49


int compare_feature(s_feature *feat1,int n1,s_feature *feat2,int n2)
{	
	sic_log("比较特征");

	int i,k,m = 0;
	s_feature **nbrs,*feat;
	double d0,d1;
	struct kd_node *kd_root;
//	sic_log("%lu,%lu",feat1,feat2);	
	sic_log("%d,%d",n1,n2);	
	if(!feat1||!feat2){
		sic_log("feat null");
		return -1;
	}

	kd_root = kdtree_build( feat2, n2 );

	for( i = 0; i < n1; i++ )
	{
		feat = feat1 + i;
		k = kdtree_bbf_knn( kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );
		if( k == 2 )
		{
			d0 = descr_dist_sq( feat, nbrs[0] );
			d1 = descr_dist_sq( feat, nbrs[1] );
			if( d0 < d1 * NN_SQ_DIST_RATIO_THR )
			{
				m++;
				feat1[i].fwd_match = nbrs[0];
			}
		}
		free( nbrs );
	}
	kdtree_release(kd_root);
	sic_log("结果%d",m);
	return m;
}


