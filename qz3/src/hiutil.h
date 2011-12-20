#ifndef HIUTIL_H
#define HIUTIL_H

#include <highgui.h>
	
extern void show(const char *name,IplImage *img);
extern void fin(const char *name,IplImage **img);

#endif /* HIUTIL_H */
