/**
* OpenCV汉字输出
*/
#ifndef OPENCV_CJK_FONT_H
#define OPENCV_CJK_FONT_H
#include <cv.h>
#include <highgui.h>
#include <ft2build.h>
#include FT_FREETYPE_H

extern int initFont(const char *fontfile);
extern void disposeFont();
extern void setFont(CvScalar *size,float diaphaneity);
extern void restoreFont();
extern int putText(IplImage *img, const char *text, CvPoint pos);
extern int putColorText(IplImage *img, const char *text,
						CvPoint pos, CvScalar color);

#endif // OPENCV_CJK_FONT_H
