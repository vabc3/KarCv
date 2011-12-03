#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <cv.h>
#define BITS IPL_DEPTH_8U
#define DEPS (1<<BITS)
#define YSCALE	255


extern void split(IplImage *src,IplImage **rgb);
extern void merge(IplImage *dst,IplImage **rgb);
extern void transfers();
extern void makeHistogramArrays();

extern IplImage *makeHistogramImage();
extern IplImage *makeRGBHistogramADFImage();
extern IplImage *makeGrayHistogramImage(float *s);
extern uchar *getADFArray() __attribute__((deprecated));
void makeHistogramArray();
IplImage *transfer(IplImage *src,uchar *ar);

#endif //HISTOGRAM_H
