#include "hiutil.h"

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

