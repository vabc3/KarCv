#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <cv.h>
#define BITS IPL_DEPTH_8U
#define DEPS (1<<BITS)

extern IplImage *makeRGBHistogramADFImage();
extern IplImage *makeGrayHistogramADFImage();
extern uchar *getADFArray();

#endif //HISTOGRAM_H
