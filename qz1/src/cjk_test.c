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
	m_fontSize.val[0] = 60;      // �����С
	m_fontSize.val[1] = 0.5;   // �հ��ַ���С����
	m_fontSize.val[2] = 0.1;   // �����С����
	m_fontSize.val[3] = 0;      // ��ת�Ƕ�(��֧��)


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

