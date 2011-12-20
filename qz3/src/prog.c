#include <cv.h>
#include <cxcore.h>
#include <stdlib.h>
#include <stdio.h>
#include "hiutil.h" 
#include "canny.h"

const char *srcP    = "Source Pic";
const char *srcC    = "Source Canny";

int main( int argc, char** argv )
{
	IplImage* pImg = NULL; 
	IplImage* pCanny = NULL;

	int low=-1,high=-1;

	if( argc < 2 ||(pImg = cvLoadImage( *(argv+1), 0)) == NULL ){
		fprintf(stderr,"%s <file> [low_threshold] [high_threshold]\n",*(argv));
		return -1;
	}

	if(argc >= 4){
		low 	= atoi(*(argv+2)); 
		high	= atoi(*(argv+3));
	}

	pCanny = cvCreateImage(cvGetSize(pImg),IPL_DEPTH_8U,1);
	cvCannyA(pImg, pCanny, low , high , 3);

	show(srcP,pImg);
	show(srcC,pCanny);

	cvWaitKey(0); //等待按键
	cvSaveImage("save.jpg",pCanny,0);
	fin(srcP,&pImg);
	fin(srcC,&pCanny);

	return 0;

}
