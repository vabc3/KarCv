#include "util.h"
#include <highgui.h>

void show(const char *name,IplImage *img)
{
	cvNamedWindow(name,1);
	cvShowImage(name,img);
	cvWaitKey(0);

}

void fin(const char *name,IplImage **img)
{
	cvDestroyWindow(name);
	cvReleaseImage(img);
}

