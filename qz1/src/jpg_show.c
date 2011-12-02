/*
 * Display a jpg picture
 *
 */
#include<stdio.h>
#include<cv.h>
#include<highgui.h>

const char *IMG		= "Color_Image";
const char *IMGGRAY	= "Gray_Image";

int main(int argc, char** argv){
	if(argc < 3){
		fprintf(stderr,"Usage:%s <imgfile> <toimg>\n",*argv);
		return 1;
	}
	IplImage *img;
	CvMat *gray;
	img = cvLoadImage(*(argv+1),CV_LOAD_IMAGE_UNCHANGED);
	
	if(img==NULL){
		fprintf(stderr,"Error opening file %s.\n",*(argv+1));
		return 2;
	}

	cvNamedWindow(IMG, CV_WINDOW_AUTOSIZE );
	cvShowImage(IMG, img );
	cvWaitKey(0);
	cvDestroyWindow(IMG);

	gray = cvCreateMat(img->height, img->width, CV_8UC1);
	cvCvtColor(img,gray,CV_RGB2GRAY);
	cvReleaseImage(&img);

	cvNamedWindow(IMGGRAY, CV_WINDOW_AUTOSIZE );
	cvShowImage(IMGGRAY, gray );
	cvWaitKey(0);
	cvDestroyWindow(IMGGRAY);

	cvSaveImage(*(argv+2),gray,0);


	cvReleaseMat(&gray);

	return 0;
}
