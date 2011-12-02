#include "cjk_font.h"

const char *IMG     = "Test_Image";

int main(int argc,char **argv)
{
	IplImage *img;
	img = cvLoadImage("12.jpg",CV_LOAD_IMAGE_UNCHANGED);
	if(initFont(*(argv+1))){
		return 1;
	}
	CvPoint cp=cvPoint(40,440);

	CvScalar m_fontSize;
	m_fontSize.val[0] = 60;      // 字体大小
	m_fontSize.val[1] = 0.5;   // 空白字符大小比例
	m_fontSize.val[2] = 0.1;   // 间隔大小比例
	m_fontSize.val[3] = 0;      // 旋转角度(不支持)


	setFont(&m_fontSize,.4f);
	putText(img,*(argv+2),cp);
//	putColorText(img,*(argv+2),cp,CV_RGB(2,0,255));
	disposeFont();
	cvNamedWindow(IMG, CV_WINDOW_AUTOSIZE);
	cvShowImage(IMG, img );
	cvWaitKey(0);
	cvDestroyWindow(IMG);

	return 0;
}

