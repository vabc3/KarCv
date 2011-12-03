#include "histogram.h"

static void drawLine(IplImage *sa,CvScalar color,float *s);

void merge(IplImage *dst,IplImage **rgb)
{

	cvMerge(*(rgb+2),*(rgb+1),*(rgb+0),0,dst);
}

void transfers(IplImage **src,IplImage **dst,uchar (*tfs)[DEPS])
{
	int i;
	for(i=0;i<3;i++)
		*(dst+i)	= transfer(*(src+i),*(tfs+i));

}

void split(IplImage *src,IplImage **rgb)
{
	*rgb = cvCreateImage( cvGetSize(src), 8, 1);
	*(rgb+1) = cvCreateImage( cvGetSize(src), 8, 1);
	*(rgb+2) = cvCreateImage( cvGetSize(src), 8, 1);
	cvCvtPixToPlane(src,*(rgb+2),*(rgb+1),*rgb,0);
}

void makeHistogramArrays(IplImage **rgb,float (*ar)[DEPS])
{
	float r[DEPS];
	makeHistogramArray(*rgb,r,*(ar));
    makeHistogramArray(*(rgb+1),r,*(ar+1));
	makeHistogramArray(*(rgb+2),r,*(ar+2));
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

IplImage *makeRGBHistogramADFImage(float *r,float *g,float *b)
{
	IplImage *sa = cvCreateImage(cvSize(DEPS,DEPS),BITS,3);
	cvZero(sa);
	drawLine(sa,CV_RGB(255,0,0),r);
	drawLine(sa,CV_RGB(0,255,0),g);
	drawLine(sa,CV_RGB(0,0,255),b);
	return sa;
}


IplImage *makeGrayHistogramImage(float *s)
{
	IplImage *sa = cvCreateImage(cvSize(DEPS,YSCALE),BITS,1);
	cvZero(sa);
	drawLine(sa,CV_RGB(255,255,255),s);
	return sa;
}

void drawLine(IplImage *sa,CvScalar color,float *s)
{	
	CvPoint p0,p1;
	int i,y;

	y	= sa->height;
	p0	= cvPoint(0,y);

	for(i=0;i<DEPS;i++){
		p1=cvPoint(i,y*(1-*(s+i)));
		cvLine(sa,p0,p1,color,1,CV_AA,0);
		p0=p1;
	}

}


void makeHistogramArray(IplImage *img,float *ar,float *adf)
{
	int i,hist_size = DEPS;
	CvHistogram* hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,0,1);
	cvCalcHist(&img,hist,0,0);
	cvNormalizeHist(hist,1.0);

	*(ar)=*(adf)=cvQueryHistValue_1D(hist,0);

	for(i=1;i<hist_size;i++)
	{
		*(ar+i)=cvQueryHistValue_1D(hist,i);
		*(adf+i)=*(adf+i-1)+*(ar+i);
	}
	cvReleaseHist(&hist);
}

uchar *getADFArray(IplImage *img) 
{
	uchar *rt;
	rt=(uchar*)malloc(DEPS*sizeof(uchar));
	int hist_size = DEPS;
	CvHistogram* hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,0,1);
	cvCalcHist(&img,hist,0,0);
	cvNormalizeHist(hist,1.0);
	float m=0;
	int i;
	for(i=0;i<hist_size;i++)
	{
		m+=cvQueryHistValue_1D(hist,i);
		rt[i]=(DEPS-1)*m;
	}

	return rt;
}

IplImage *transfer(IplImage *src,uchar *ar)
{
	IplImage *dst 	= cvCloneImage(src);
	CvMat *T_mat	= cvCreateMatHeader(1,DEPS,CV_8UC1);
	cvSetData(T_mat,ar,256);
	cvLUT(src,dst,T_mat);
	return dst;
}

