#include "histogram.h"

static IplImage *drawLine();

IplImage *makeRGBHistogramADFImage(uchar *r,uchar *g,uchar *b)
{
	IplImage *sa = cvCreateImage(cvSize(DEPS,DEPS),BITS,3);
	cvZero(sa);
	drawLine(sa,CV_RGB(255,0,0),r);
	drawLine(sa,CV_RGB(0,255,0),g);
	drawLine(sa,CV_RGB(0,0,255),b);
	return sa;
}


IplImage *makeGrayHistogramADFImage(uchar *s)
{	
	IplImage *sa = cvCreateImage(cvSize(DEPS,DEPS),BITS,1);
	cvZero(sa);
	drawLine(sa,CV_RGB(255,255,255),s);
	return sa;
}

IplImage *drawLine(IplImage *sa,CvScalar color,uchar *s)
{	
	CvPoint p0,p1;
	int i,y;

	y	= sa->height;
	p0	= cvPoint(0,y);

	for(i=0;i<DEPS;i++){
		p1=cvPoint(i,y-*(s+i));
		//		printf("%d.%d\n",i,s[i]);
		cvLine(sa,p0,p1,color,1,8,0);
		p0=p1;
	}

	return sa;
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


