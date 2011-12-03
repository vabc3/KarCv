#include "histogram.h"
#include <highgui.h>

const char *IMG     = "Ce";

int main()
{	float s[DEPS];
	int i;
	IplImage *a;

	for(i=0;i<DEPS;i++){
		s[i]=(1.0*i/DEPS);
		s[i]*=s[i]*s[i];
		if(i==DEPS-1)break;
	}
	a=makeGrayHistogramImage(s);
	cvNamedWindow(IMG, 1 );
	cvShowImage(IMG,a);
	cvWaitKey(0);
	cvReleaseImage(&a);


	return 0;
}
