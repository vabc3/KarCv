#include <stdio.h>
#include "hiutil.h"
#include "histogram.h"

const char *srcP	= "Source Pic";
const char *srcA	= "Source ADF";
const char *dstP	= "Dest	Pic";
const char *dstA	= "Dest ADF";

void maketf(uchar *tf,float *f){
	int i;
	for(i=0;i<DEPS;i++)
		*(tf+i)=*(f+i)*255;
}

int main(int argc, char** argv){
	IplImage *src,*dst,*srca,*dsta;
	float r[DEPS],ra[DEPS],g[DEPS],ga[DEPS],b[DEPS],ba[DEPS];
	uchar tf[DEPS];

	src=cvLoadImage(*(argv+1),1);
	IplImage* RedChannel = cvCreateImage( cvGetSize(src), 8, 1);
	IplImage* GreenChannel = cvCreateImage( cvGetSize(src), 8, 1);
	IplImage* BlueChannel = cvCreateImage( cvGetSize(src), 8, 1);
	cvCvtPixToPlane(src,BlueChannel,GreenChannel,RedChannel,0);

	makeHistogramArray(RedChannel,r,ra);
	makeHistogramArray(GreenChannel,g,ga);
	makeHistogramArray(BlueChannel,b,ba);

	srca=makeRGBHistogramADFImage(ra,ga,ba);

	IplImage *nr,*ng,*nb;

	maketf(tf,ra);	
	nr=transfer(RedChannel,tf);
	maketf(tf,ga);
	ng=transfer(GreenChannel,tf);
	maketf(tf,ba);
	nb=transfer(BlueChannel,tf);
	
	dst=cvCloneImage(src);
	cvMerge(nr,GreenChannel,BlueChannel,0,dst);
	
	makeHistogramArray(nr,r,ra);
	makeHistogramArray(ng,g,ga);
	makeHistogramArray(nb,b,ba);

	dsta=makeRGBHistogramADFImage(ra,ga,ba);
	
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
