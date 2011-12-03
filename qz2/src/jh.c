#include <cv.h>
#include <stdio.h>
#include "hiutil.h"
#include "histogram.h"

const char *srcP    = "Source Pic";
const char *srcA    = "Source ADF";
const char *dstP    = "Dest Pic";
const char *dstA    = "Dest ADF";

int main( int argc, char** argv ) 
{
	IplImage *src, *dst, *sa, *sd;
	uchar T[DEPS];
	int x;
	float ar[DEPS],lt[DEPS];

	if( argc != 2 || (src=cvLoadImage(argv[1], 0)) == NULL) 
		return -1;

	makeHistogramArray(src,ar,lt);
	sa=makeGrayHistogramImage(lt);

	for( x = 0; x < DEPS; x++ )
	{
		T[x] = (uchar) (255 * lt[x]);
	}
	dst=transfer(src,T);
	
	makeHistogramArray(dst,ar,lt);
	sd=makeGrayHistogramImage(lt);

	show(srcA,sa);
	show(dstA,sd);
	cvWaitKey(0);
	fin(srcA,&sa);
	fin(dstA,&sd);
	
	return 0;
}
