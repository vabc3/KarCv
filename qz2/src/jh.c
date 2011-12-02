#include "cv.h"
#include "highgui.h"
#include "histogram.h"
#include <stdio.h>
#define HDIM    256    // bin of HIST, default = 256

int main( int argc, char** argv ) 
{
	IplImage *src = 0, *dst = 0;
	CvHistogram *hist = 0;

	int n = HDIM;     
	double nn[HDIM];
	uchar T[HDIM];
	CvMat *T_mat;
	int x;
	int sum = 0; // sum of pixels of the source image 图像中象素点的总和
	double val = 0;

	if( argc != 2 || (src=cvLoadImage(argv[1], 0)) == NULL)  // force to gray image
		return -1;

	//  cvNamedWindow( "source", 1 );
	cvNamedWindow( "sourceA", 1 );
	//    cvNamedWindow( "result", 1 );
	cvNamedWindow( "resultA", 1 );
	int xlen=cvGetSize(src).width;
	//    xlen=256;
	IplImage* sa;// = cvCreateImage(cvSize(xlen,256),8,1);
	IplImage* sd = cvCreateImage(cvSize(xlen,256),8,1);
	//    cvSet(sa,0,0);

	// calculate histgram 计算直方图
	hist = cvCreateHist( 1, &n, CV_HIST_ARRAY, 0, 1 );  
	cvCalcHist( &src, hist, 0, 0 ); 

	// Create Accumulative Distribute Function of histgram
	val = 0;
	for ( x = 0; x < n; x++)
	{  //printf("%d,%lf\n",x,cvGetReal1D (hist->bins, x));
		val = val + cvGetReal1D (hist->bins, x);
		nn[x] = val;
	}

	// Compute intensity transformation 计算变换函数的离散形式
	sum = src->height * src->width;



	for( x = 0; x < n; x++ )
	{
		T[x] = (uchar) (255 * nn[x] / sum); // range is [0,255]
		//        p1=cvPoint(x,T[x]);
		//     cvLine(sa,p0,p1,CV_RGB(255,255,255),1,8,0);
		//    p0=p1;
		//	printf("%d.%lf/%d->%d\n",x,nn[x],sum,T[x]);
	}
	sa=makeGrayHistogramADFImage(T);


	// Do intensity transform for source image
	dst = cvCloneImage( src );
	T_mat = cvCreateMatHeader( 1, 256, CV_8UC1 );
	cvSetData( T_mat, T, 256);    
	// directly use look-up-table function 直接调用内部函数完成 look-up-table 的过程
	cvLUT( src, dst, T_mat );


	hist = cvCreateHist( 1, &n, CV_HIST_ARRAY, 0, 1 );  
	cvCalcHist( &dst, hist, 0, 0 ); 

	// Create Accumulative Distribute Function of histgram
	val = 0;
	for ( x = 0; x < n; x++)
	{
		val = val + cvGetReal1D (hist->bins, x);

		nn[x] = val;
		// printf("%d,%lf\n",x,cvGetReal1D (hist->bins, x));
	}

	for( x = 0; x < n; x++ )
	{
		T[x] = (uchar) (255 * nn[x] / sum); // range is [0,255]
		//	printf("%d.%lf/%d->%d\n",x,nn[x],sum,T[x]);
	}
	sd=makeGrayHistogramADFImage(T);


	cvShowImage( "source", src );
	cvShowImage( "sourceA", sa );
	cvShowImage( "result", dst );
	cvShowImage( "resultA", sd);



	cvWaitKey(0);
	cvDestroyWindow("sourceA");
	cvDestroyWindow("resultA");
	cvDestroyWindow("source");
	cvDestroyWindow("result");
	cvReleaseImage( &src );
	cvReleaseImage( &sa );
	cvReleaseImage( &sd );
	cvReleaseImage( &dst );
	cvReleaseHist ( &hist );

	return 0;
}
