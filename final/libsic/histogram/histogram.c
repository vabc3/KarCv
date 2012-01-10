#include "histogram.h"
#include <stdio.h>

static void drawLine(IplImage *sa,CvScalar color,float *s);
static void makeHistogramArray(IplImage *img,float *ar);

void merge(IplImage *dst,IplImage **rgb)
{

	cvMerge(*(rgb+2),*(rgb+1),*(rgb+0),0,dst);
}

void split(IplImage *src,IplImage **rgb)
{
	*rgb = cvCreateImage( cvGetSize(src), 8, 1);
	*(rgb+1) = cvCreateImage( cvGetSize(src), 8, 1);
	*(rgb+2) = cvCreateImage( cvGetSize(src), 8, 1);
	cvCvtPixToPlane(src,*(rgb+2),*(rgb+1),*rgb,0);
}

void makeHistogramArrays(IplImage **rgb,float (*r)[DEPS])
{
	makeHistogramArray(*rgb,*(r));
    makeHistogramArray(*(rgb+1),*(r+1));
	makeHistogramArray(*(rgb+2),*(r+2));
}

IplImage *makeHistogramImage(int dims,float (*ar)[DEPS])
{
	//	printf("%d %d\n",*ar,*(ar+1));	
	IplImage *sa = cvCreateImage(cvSize(DEPS,YSCALE),BITS,3);
	cvZero(sa);
	drawLine(sa,CV_RGB(255,0,0),*(ar));
	drawLine(sa,CV_RGB(0,255,0),*(ar+1));
	drawLine(sa,CV_RGB(0,0,255),*(ar+2));
	return sa;
}


void drawLine(IplImage *sa,CvScalar color,float *s)
{	
	CvPoint p0,p1;
	int i,y;

	y	= sa->height;
	p0	= cvPoint(0,y);
	for(i=1;i<DEPS;i++){
//		printf("%d.\"%f,%f\n",i,*(s+i),*s);
		p1=cvPoint(i,y*(1-1.0*(*(s+i))));
		cvLine(sa,p0,p1,color,1,CV_AA,0);
		p0=p1;
	}

}

static void makeHistogramArray(IplImage *img,float *adf)
{
	float ar[DEPS];
	int i,hist_size = DEPS;
	CvHistogram* hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,0,1);
	cvCalcHist(&img,hist,0,0);
	cvNormalizeHist(hist,1.0);

	*(ar)=*(adf)=cvQueryHistValue_1D(hist,0);

	for(i=1;i<hist_size;i++){
		*(ar+i)		= cvQueryHistValue_1D(hist,i);
		*(adf+i)	= *(adf+i-1)+*(ar+i);
	}
	cvReleaseHist(&hist);
}

