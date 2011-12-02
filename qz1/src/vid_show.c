#include <highgui.h>
#include "cjk_font.h"
#define FPS 18
#define KEY_ESC 27

const int sec 		= 1000 / FPS ;
const char *WINDOW	= "Play_Video";

int main( int argc, char **argv ) {

	if(argc<11){
		fprintf(stderr,
				"Usage %s <videofile> <font> <words> <size> <x> <y> <r> <g> <b> <transparency>\n",*argv);
		return 1;
	}


	cvNamedWindow( WINDOW, CV_WINDOW_AUTOSIZE );
	CvCapture* capture = cvCreateFileCapture(*(argv+1));
	if(capture==NULL){
		fprintf(stderr,"Error open videofile %s.\n",*(argv+1));
		return 1;
	}

	if(initFont(*(argv+2))){
		return 1;
	}

	CvPoint cp = cvPoint(atoi(*(argv+5)),atoi(*(argv+6)));

	CvScalar m_fontSize;
	m_fontSize.val[0] = atoi(*(argv+4));
	m_fontSize.val[1] = 0.5;
	m_fontSize.val[2] = 0.1;
	m_fontSize.val[3] = 0;
	setFont(&m_fontSize,atof(*(argv+10)));

	IplImage* frame;
	CvScalar color = CV_RGB(atoi(*(argv+7)),atoi(*(argv+8)),atoi(*(argv+9)));

	while(1) {
		frame = cvQueryFrame(capture);
		putColorText(frame,*(argv+3),cp,color);
		if( !frame ) break;
		cvShowImage(WINDOW, frame );
		char c = cvWaitKey(sec);
		if( c == KEY_ESC ) break;
	}

	cvReleaseCapture( &capture );
	cvDestroyWindow(WINDOW);
	disposeFont();

	return 0;
}
