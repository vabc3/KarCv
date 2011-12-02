#include "histogram.h"
#include <highgui.h>

const char *IMG     = "Ce";

int main()
{	uchar s[DEPS],i;
	IplImage *a;

	for(i=0;i<DEPS;i++){
		s[i]=i;
		if(i==DEPS-1)break;
	}
	a=makeGrayHistogramADFImage(s);
	cvNamedWindow(IMG, 1 );
	cvShowImage(IMG,a);
	cvWaitKey(0);
	cvReleaseImage(&a);


	return 0;
}
