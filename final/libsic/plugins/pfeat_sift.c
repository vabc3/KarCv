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
#include <stdio.h>
#include "util.h"
#include "sift.h"
#include "kdtree.h"
#include "pall.h"
#include "psift.h"


/* the maximum number of keypoint NN candidates to check during BBF search */
#define KDTREE_BBF_MAX_NN_CHKS 150

/* threshold on squared ratio of distances between NN and 2nd NN */
//#define NN_SQ_DIST_RATIO_THR 0.49
#define NN_SQ_DIST_RATIO_THR 0.34


int intvls = SIFT_INTVLS;
double sigma = SIFT_SIGMA;
double contr_thr = SIFT_CONTR_THR;
int curv_thr = SIFT_CURV_THR;
int img_dbl = SIFT_IMG_DBL;
int descr_width = SIFT_DESCR_WIDTH;
int descr_hist_bins = SIFT_DESCR_HIST_BINS;

static int genfeature(IplImage *img,void **out);
static int save(void *data,char *fn);
static int load(char *fn,void **data);
static float comp(void* feat1,void* feat2);
static void* gendoc(IplImage* img,void* data,char* featkey,char* dir,char* prefix);

sicpfeat psift={
	1,PRSIFT,genfeature,save,load,comp,gendoc
};


static IplImage* stack_imgs( IplImage* img1, IplImage* img2 )
{
	IplImage* stacked = cvCreateImage( cvSize( MAX(img1->width, img2->width),
				img1->height + img2->height ),
			IPL_DEPTH_8U, 3 );

	cvZero( stacked );
	cvSetImageROI( stacked, cvRect( 0, 0, img1->width, img1->height ) );
	cvAdd( img1, stacked, stacked, NULL );
	cvSetImageROI( stacked, cvRect(0, img1->height, img2->width, img2->height) );
	cvAdd( img2, stacked, stacked, NULL );
	cvResetImageROI( stacked );

	return stacked;
}


static void* gendoc(IplImage* img1,void* data,char* featkey,char* dir,char* prefix)
{
	sic_log("sift->gendoc base:%s|%s",dir,prefix);
	char buf[255];

	void *f2;
	load(featkey,&f2);

	sprintf(buf,"%s.jpg",featkey);
	IplImage *img2=cvLoadImage(buf,1);
	IplImage *img=stack_imgs(img1,img2);

	sic_sift *sf1,*sf2;
	s_feature *feat1,*feat2;
	int n1,n2;

	sf1=(sic_sift*)data;
	sf2=(sic_sift*)f2;
	feat1=sf1->feat;feat2=sf2->feat;
	n1=sf1->n;n2=sf2->n;
	int i,k,m = 0;
	s_feature **nbrs,*feat;
	double d0,d1;
	struct kd_node *kd_root;
	CvPoint pt1,pt2;

	kd_root = kdtree_build( feat2, n2 );
	for( i = 0; i < n1; i++ ){
		feat = feat1 + i;
		k = kdtree_bbf_knn( kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );
		if( k == 2 ){
			d0 = descr_dist_sq( feat, nbrs[0] );
			d1 = descr_dist_sq( feat, nbrs[1] );
			if( d0 < d1 * NN_SQ_DIST_RATIO_THR ){
				pt1 = cvPoint( cvRound( feat->x ), cvRound( feat->y ) );
				pt2 = cvPoint( cvRound( nbrs[0]->x ), cvRound( nbrs[0]->y ) );
				pt2.y += img1->height;
				cvLine( img, pt1, pt2, CV_RGB(2,0,255), 1, 8, 0 );
				m++;
				feat1[i].fwd_match = nbrs[0];
			}
		}
		free( nbrs );
	}

	kdtree_release(kd_root);


	sprintf(buf,"%s/%ssift.jpg",dir,prefix);
	cvSaveImage(buf,img,NULL);
//	cvReleaseImage(&img);
//	cvReleaseImage(&img1);
//	cvReleaseImage(&img2);

//	float ft=comp(data,f2);
	char* rt1,*rt2;
	sprintf(buf,"特征匹配相似处%d",m);
	rt1=(char*)malloc(strlen(buf)+2);
	strcpy(rt1,buf);

	sprintf(buf,"%s/%ssift.jpg",dir,prefix);
	rt2=(char*)malloc(strlen(buf)+2);
	strcpy(rt2,buf);
	void **rt=(void**)malloc(2*sizeof(void*));
	*(rt)=rt1;
	*(rt+1)=rt2;	

	return rt;
}


static int genfeature(IplImage *img,void **out)
{
	sic_log("generate in sift");
	int n;
	s_feature *feat;
	n = _sift_features( img, &feat, intvls, sigma, contr_thr, curv_thr,
			img_dbl, descr_width, descr_hist_bins );
	sic_log("n=%d",n);
	sic_sift *sf=(sic_sift*)malloc(sizeof(sic_sift));

	sf->n=n;
	sf->feat=feat;
	*out = (void*)sf;
	return 0;
}

static int save(void *data,char *fn)
{
	sic_log("save in sift");	
	sic_sift *sf	=(sic_sift*)data;

	char buf[512];
	sprintf(buf,"%s.sift",fn);

	sic_log("SaveFeatTo:%s",buf);

	export_features(buf,sf->feat,sf->n);
	return 0;
}

static int load(char *fn,void **data)
{
	sic_sift *sf=NULL;
	*data=NULL;
	struct feature* feat=NULL;
	int n;
	if(!fn){
		sic_log("name NULL");
		return -1;
	}
	char buf[512];
	sprintf(buf,"%s.sift",fn);
	sic_log("LoadFeatFrom:%s",buf);
	n = import_features( buf, FEATURE_LOWE, &feat );
	if(n==-1){
		sic_log("Feat import error");
		return -1;
	}
	sf=(sic_sift*)malloc(sizeof(sic_sift));
	sf->n=n;
	sf->feat=feat;
	sic_log("load in sift:n=%d",n);
	*data=sf;
	return 0;
}



static float comp(void *f1,void* f2)
{	
	sic_log("比较特征");
	sic_sift *sf1,*sf2;

	s_feature *feat1,*feat2;
	int n1,n2;

	sf1=(sic_sift*)f1;
	sf2=(sic_sift*)f2;
	feat1=sf1->feat;feat2=sf2->feat;
	n1=sf1->n;n2=sf2->n;


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
	return 1.0*m/n1;
}

