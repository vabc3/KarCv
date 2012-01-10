#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <cv.h>
#define BITS IPL_DEPTH_8U
#define DEPS (1<<BITS)
#define YSCALE	255


extern void split(IplImage *src,IplImage **rgb);
extern void merge(IplImage *dst,IplImage **rgb);
extern IplImage *makeRGBHistogramADFImage();
extern IplImage *makeGrayHistogramImage(float *s);
IplImage *transfer(IplImage *src,uchar *ar);

extern void makeHistogramArrays(IplImage **rgb,float (*ar)[DEPS]);
extern IplImage *makeHistogramImage(int dims,float (*ar)[DEPS]);
#endif //HISTOGRAM_H
