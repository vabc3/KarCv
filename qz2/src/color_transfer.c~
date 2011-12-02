#include <stdio.h>
#include <highgui.h>
#include "histogram.h"

const char *srcP	= "Source Pic";
const char *srcA	= "Source ADF";
const char *dstP	= "Dest	Pic";
const char *dstA	= "Dest ADF";

void show(const char *name,IplImage *img)
{
	cvNamedWindow(name,1);
	cvShowImage(name,img);
}

void fin(const char *name,IplImage **img)
{
	cvDestroyWindow(name);
	cvReleaseImage(img);
}


int main(int argc, char** argv){
	IplImage *src,*dst,*srca,*dsta;
	uchar *r,*g,*b;
	src=cvLoadImage(*(argv+1),1);
	IplImage* RedChannel = cvCreateImage( cvGetSize(src), 8, 1);
	IplImage* GreenChannel = cvCreateImage( cvGetSize(src), 8, 1);
	IplImage* BlueChannel = cvCreateImage( cvGetSize(src), 8, 1);
	cvCvtPixToPlane(src,BlueChannel,GreenChannel,RedChannel,0);

	r=getADFArray(RedChannel);
	g=getADFArray(GreenChannel);
	b=getADFArray(BlueChannel);

	srca=makeRGBHistogramADFImage(r,g,b);

	IplImage *nr,*ng,*nb;
	nr=cvCloneImage(RedChannel);
	ng=cvCloneImage(GreenChannel);
	nb=cvCloneImage(BlueChannel);



	CvMat *T_mat;
    T_mat = cvCreateMatHeader( 1, 256, CV_8UC1 );
	cvSetData( T_mat, r, 256);
	cvLUT(RedChannel,nr,T_mat);



	cvSetData( T_mat, g, 256);
	cvLUT(GreenChannel,ng,T_mat);


	cvSetData( T_mat, b, 256);
	cvLUT(BlueChannel,nb,T_mat);

	dst=cvCloneImage(src);
	cvMerge(nr,GreenChannel,BlueChannel,0,dst);
	
	r=getADFArray(nr);
	g=getADFArray(ng);
	b=getADFArray(nb);
	dsta=makeRGBHistogramADFImage(r,g,b);	
	
	show(srcP,src);
	show(srcA,srca);
	show(dstP,dst);
	show(dstA,dsta);
	cvWaitKey(0);

	fin(srcP,&src);
	fin(srcA,&srca);
	fin(dstP,&dst);
	fin(dstA,&dsta);
	return 0;
}
