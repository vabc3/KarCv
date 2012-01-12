/*
 * =====================================================================================
 *
 *       Filename:  pfeat_hist.c
 *
 *    Description:  直方图插件
 *
 *        Version:  1.0
 *        Created:  2012年01月09日 21时58分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Karata Lau (kl), vabc3h@gmail.com
 *        Company:  ZJU
 *
 * =====================================================================================
 */
#include "pall.h"
#include "phist.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <highgui.h>
static int genfeature(IplImage *img,void **out);
static int save(void *data,char *fn);
static int load(char *fn,void **data);
static float comp(void* feat1,void* feat2);
static void* gendoc(IplImage* img,void* data,char* featkey,char* dir,char* prefix);

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


sicpfeat phist={
	2,PRHIST,genfeature,save,load,comp,gendoc
};

static void* gendoc(IplImage* imgo,void* data,char* featkey,char* dir,char* prefix)
{
	sic_log("hist->gendoc base:%s|%s",dir,prefix);

	char buf[255];

	void *f2;

	load(featkey,&f2);

	float ft=comp(data,f2);
	char base[255];
	sprintf(base,"%s/%s",dir,prefix);
	IplImage *img1,*img2;
	sic_hist* s;
	
	s	= (sic_hist*)data;
	img1=makeHistogramImage(3,s->sm);
//	sprintf(buf,"%shist1.jpg",base);
//	cvSaveImage(buf,img,NULL);	
//	cvReleaseImage(&img);

	s	= (sic_hist*)f2;
	img2=makeHistogramImage(3,s->sm);


	IplImage *img=stack_imgs(img1,img2);

	sprintf(buf,"%shist2.jpg",base);
	cvSaveImage(buf,img,NULL);	
	cvReleaseImage(&img);


		



	char* rt1,*rt2;
	sprintf(buf,"直方图相似度%.2f",ft);
	rt1=(char*)malloc(strlen(buf)+2);
	strcpy(rt1,buf);

	sprintf(buf,"%shist2.jpg",base);
	rt2=(char*)malloc(strlen(buf)+2);
	strcpy(rt2,buf);
	void **rt=(void**)malloc(2*sizeof(void*));
	*(rt)=rt1;
	*(rt+1)=rt2;

	return rt;
}

static int genfeature(IplImage *img,void **out)
{
	sic_log("hist->gen");
	IplImage *rgb[3];
	float sm[3][DEPS];

	split(img,rgb);
	makeHistogramArrays(rgb,sm);

	sic_hist *s=(sic_hist*)malloc(sizeof(sic_hist));
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<DEPS;j++)
			s->sm[i][j]=sm[i][j];
	*out=(void*)s;


	//	 IplImage* ig=makeHistogramImage(3,s->sm);
	//   show("ig",ig);
	//



	return 0;
}
static int save(void *data,char *fn)
{
	sic_log("hist->save");

	char buf[512];
	sprintf(buf,"%s.hist",fn);

	sic_hist *s	= (sic_hist*)data;

	FILE* fp	= fopen(buf,"w");
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<DEPS;j++)
			fprintf(fp,"%f\t",s->sm[i][j]);

	fclose(fp);
	return 0;
}

static int load(char *fn,void **data)
{
	sic_log("hist->load {%s}",fn);
	IplImage *ig;
	sic_hist *s=(sic_hist*)malloc(sizeof(sic_hist));

	char buf[512];
	sprintf(buf,"%s.hist",fn);

	FILE* fp    = fopen(buf,"r");
	int i,j,t;
	for(i=0;i<3;i++)
		for(j=0;j<DEPS;j++)
			t=fscanf(fp,"%f\t",&(s->sm[i][j]));

	fclose(fp);

	//	ig=makeHistogramImage(3,s->sm);
	//	show("ig",ig);
	*data=s;
	return 0;
}

static float comp(void* feat1,void* feat2)
{
	sic_log("hist->comp");
	sic_hist* s1	= (sic_hist*)feat1;
	sic_hist* s2	= (sic_hist*)feat2;

	int i,j;
	float cal[3],lag,res;

	for(i=0;i<3;i++){
		cal[i]=0;
		for(j=0;j<DEPS;j++){
			lag=(s1->sm[i][j]-s2->sm[i][j]);
			if(lag<0)lag=-lag;
			cal[i]+=lag;
		}
		cal[i]/=(DEPS);
		//		sic_log("Each cal %f",cal[i]);
	}
	res=powf(cal[0]*cal[1]*cal[2],1.0/3);

	return 1-res;
}

