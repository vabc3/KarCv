#include <stdio.h>
#include "hiutil.h"
#include "histogram.h"

const char *srcP	= "Source Pic";
const char *srcA	= "Source ADF";
const char *studyP	= "StudyP";
const char *studyA	= "Study";
const char *dstP	= "Dest	Pic";
const char *dstA	= "Dest ADF";

void studys(uchar (*tfs)[DEPS],float (*f)[DEPS],float (*src)[DEPS]){
	int i,j,k;

	for(i=0;i<3;i++){
		for(j=0;j<DEPS;j++){
			for(k=0;k<DEPS;k++){
				if(*(*(f+i)+k)>*(*(src+i)+j))
					break;
			}
			*(*(tfs+i)+j)=k;
		}
	}
}

void maketfs(uchar (*tfs)[DEPS],float (*f)[DEPS]){
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<DEPS;j++){
			*(*(tfs+i)+j)=*(*(f+i)+j)*255;
	}
}

void maketf(uchar *tf,float *f){
	int i;
	for(i=0;i<DEPS;i++)
		*(tf+i)=*(f+i)*255;
}

int main(int argc, char** argv){
	IplImage *src,*dst,*srca,*dsta,*study,*studya;
	IplImage *rgb[3],*nrgb[3];
	uchar tfs[3][DEPS];
	float m[3][DEPS],nm[3][DEPS],sm[3][DEPS];


	if(argc!=3){
			printf("%s <source> <study>\n",*argv);
			return 1;
	}

//��ȡԴ��ѧϰͼƬ
	src		= cvLoadImage(*(argv+1),1);
	study	= cvLoadImage(*(argv+2),1);

	split(study,rgb);
	makeHistogramArrays(rgb,sm);
	studya	= makeHistogramImage(3,sm);


	split(src,rgb);
	makeHistogramArrays(rgb,m);
	srca=makeHistogramImage(3,m);

	
//	maketfs(tfs,m);
	studys(tfs,sm,m);

	transfers(rgb,nrgb,tfs);
	dst=cvCloneImage(src);
	merge(dst,nrgb);

	makeHistogramArrays(nrgb,nm);
	dsta=makeHistogramImage(3,nm);

	cvSaveImage("save.jpg",dst,0);

	show(srcP,src);
	show(srcA,srca);
	show(studyA,studya);
	show(studyP,study);
	show(dstP,dst);
	show(dstA,dsta);
	cvWaitKey(0);
	fin(srcP,&src);
	fin(srcA,&srca);
	fin(studyP,&study);
	fin(studyA,&studya);
	fin(dstP,&dst);
	fin(dstA,&dsta);
	return 0;
}
