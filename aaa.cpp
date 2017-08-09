
#include<io.h>
#include<vector>
#include "cv.h"  
#include "highgui.h"  
#include "cxcore.h"  
#include <iostream> 
#include <string>
#include "opencv2/opencv.hpp"
/*#include "FreeImage.h"  
#pragma comment(lib,"FreeImage.lib")*/

using namespace std;
using namespace cv;
#include <opencv2/opencv.hpp>  
int idx = 1;
const char *pstrSrcWindowsTitle = "ԭͼ";
const char *pstrDestWindowsTitle_1 = "��ԭͼ��ʴ֮��";
const char *pstrDestWindowsTitle_2 = "��ԭͼ����֮��";
const char *pstrDestWindowsTitle_3 = "�Ը�ʴ����ͼƬ������";

#include <cassert>

/*
IplImage*  gif2ipl(const char* filename)
{
	FreeImage_Initialise();         //load the FreeImage function lib    
	FREE_IMAGE_FORMAT fif = FIF_GIF;
	FIBITMAP* fiBmp = FreeImage_Load(fif, filename, GIF_DEFAULT);
	FIMULTIBITMAP * pGIF = FreeImage_OpenMultiBitmap(fif, filename, 0, 1, 0, GIF_PLAYBACK);
	//  FIBITMAPINFO fiBmpInfo = getfiBmpInfo(fiBmp);    
	int gifImgCnt = FreeImage_GetPageCount(pGIF);
	FIBITMAP * pFrame;
	int width, height;
	width = FreeImage_GetWidth(fiBmp);
	height = FreeImage_GetHeight(fiBmp);
	IplImage * iplImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	iplImg->origin = 1;//should set to 1-top-left structure(Windows bitmap style)    
	RGBQUAD* ptrPalette = new RGBQUAD; // = FreeImage_GetPalette(fiBmp);    
	BYTE intens;
	BYTE* pIntensity = &intens;
	//cvNamedWindow("gif", 0);
	//printf("gifImgCnt %d \n", gifImgCnt);
	for (int curFrame = 0; curFrame < gifImgCnt; curFrame++)
	{
		pFrame = FreeImage_LockPage(pGIF, curFrame);
		//ptrPalette = FreeImage_GetPalette(pFrame);    
		char * ptrImgDataPerLine;
		for (int i = 0; i < height; i++)
		{
			ptrImgDataPerLine = iplImg->imageData + i*iplImg->widthStep;
			for (int j = 0; j < width; j++)
			{
				//get the pixel index     
				//FreeImage_GetPixelIndex(pFrame,j,i,pIntensity);      
				FreeImage_GetPixelColor(pFrame, j, i, ptrPalette);
				ptrImgDataPerLine[3 * j] = ptrPalette->rgbBlue;
				ptrImgDataPerLine[3 * j + 1] = ptrPalette->rgbGreen;
				ptrImgDataPerLine[3 * j + 2] = ptrPalette->rgbRed;
				//ptrImgDataPerLine[3*j] = ptrPalette[intens].rgbBlue;    
				//ptrImgDataPerLine[3*j+1] = ptrPalette[intens].rgbGreen;    
				//ptrImgDataPerLine[3*j+2] = ptrPalette[intens].rgbRed;    
			}
		}

		//printf("convert curFrame end %d \n", curFrame);
		//cvShowImage("gif", iplImg);
		cvWaitKey(30);
		FreeImage_UnlockPage(pGIF, pFrame, 1);
	}
	FreeImage_Unload(fiBmp);
	FreeImage_DeInitialise();
	FreeImage_CloseMultiBitmap(pGIF, GIF_DEFAULT);
	return iplImg;
}

*/

int  main()
{
	//int idx = 0;
	IplImage* imgSrc = cvLoadImage("/opt/deep_ocr/zh.png", CV_LOAD_IMAGE_COLOR);
//	if (imgSrc == NULL){
//		imgSrc = gif2ipl("/opt/deep_ocr/yyy.gif");
//	}
	
	
//	Mat T = cvarrToMat(imgSrc);
	//resize(T, T, Size(imgSrc->height*3, imgSrc->width*9), 0, 0, CV_INTER_LINEAR);
	//IplImage imgTmp = T;
	//imgSrc = cvCloneImage(&imgTmp);

	//filename ��Ҫ��������ļ����ļ���(������׺)��	//flags ��ָ������ͼ�����ɫ����ȣ�
	//ָ������ɫ���Խ������ͼƬתΪ3ͨ��(CV_LOAD_IMAGE_COLOR),
	//	��ͨ��(CV_LOAD_IMAGE_GRAYSCALE),
	//���߱��ֲ���(CV_LOAD_IMAGE_ANYCOLOR)��
	IplImage* img_gray = cvCreateImage(cvGetSize(imgSrc), IPL_DEPTH_8U, 1);

	
	

	cvCvtColor(imgSrc, img_gray, CV_BGR2GRAY);//ת�ɻ�ɫ
	//cvFlip(img_gray, NULL, 0);

	//cvNamedWindow("�Ҷ�ͼ��");//��ʾ�Ҷ�ͼ��
	//cvShowImage("�Ҷ�ͼ��", img_gray);


//	cvSmooth(img_gray, img_gray, CV_MEDIAN, 3, 3);//��ֵģ��
//	cvShowImage("��ֵģ��", img_gray);
	
	

	cvErode(img_gray, img_gray, NULL, 1);//��ʴ��������ʾ  
	//cvShowImage(pstrDestWindowsTitle_1, img_gray);


	//cvDilate(img_gray, img_gray, NULL, 1);//���ʹ�������ʾ  ����  
	//cvShowImage(pstrDestWindowsTitle_2, img_gray);
	//cvThreshold(img_gray, img_gray,230, 255, CV_THRESH_BINARY_INV);//ȫ����ֵ
	cvAdaptiveThreshold(img_gray, img_gray,255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV,21,3);//�ֲ���ֵ
	
	

	
	//cvDilate(img_gray, img_gray, NULL, 1);//���ʹ�������ʾ  ����  
//	cvShowImage(pstrDestWindowsTitle_2, img_gray);


	CvSeq* contours = NULL;
	CvMemStorage* storage = cvCreateMemStorage(0);
	
	int count = cvFindContours(img_gray, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL);
	
	//printf("������%d", idx);
	char szName[56] = { 0 };
	int tempCount = 0;
	int x = 0;
	int y = 0;
	for (CvSeq* c = contours; c != NULL; c = c->h_next) {
		CvRect rc = cvBoundingRect(c, 0);
		//CvRect ����4�����ݳ�Ա��x,y,width,height,
		//ͨ������������Ͻ�����;��εĿ�͸���ȷ��һ�����Ρ�
		//printf("id %d ��%d �ߣ�%d\n", idx, rc.width, rc.height);
		if (rc.width<10 || rc.height<10 || rc.width>500 || rc.height>500)
		{
			continue;    // ������Ը��������Ĵ�С����ɸѡ
		}
		//��ȦȦ
//		cvDrawRect(imgSrc, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 255, 255));//CV_RGB(255, 0, 0)��
		IplImage* imgNo = cvCreateImage(cvSize(rc.width, rc.height), IPL_DEPTH_8U, 3);
		cvSetImageROI(imgSrc, rc);
		//���ڸ����ľ�������ͼ���ROI������Ȥ����
		//imgSrcֻ��ʾrc��ʶ��һ����
		cvCopy(imgSrc, imgNo);
		//���ʱ��imgSrcָʾ��ʶ�Ĳ��֣��������п���
		cvResetImageROI(imgSrc);
		//cvResetImageROI(img1);֮��img1ָʾԭ����ͼ����Ϣ
		
		x = rc.x;
		y = rc.y;
		y = y / 10 * 10;

		sprintf(szName, "/opt/deep_ocr/img/%d_%d_%d.png", x,y,idx++);
		//	cvNamedWindow(szName);
		//cvNamedWindow
		Mat M = cvarrToMat(imgNo);
		resize(M, M, Size(50, 50), 0, 0, CV_INTER_LINEAR);
		//������и������ͼ����������򣬻���ϵ��£����ԱȽ�rc.x,rc.y;
		//cvShowImage(szName, imgNo);
		//	imshow(szName, M);
		//��ͼ�������հ׵�ͼ����ȥ
		Mat imageROI;
		Mat black = imread("/opt/deep_ocr/q.png");
		imageROI = black(Rect(10, 10, M.cols, M.rows));
		M.copyTo(imageROI);


		IplImage imgTmp = black;
		IplImage *input = cvCloneImage(&imgTmp);
		IplImage* img_gray_s = cvCreateImage(cvGetSize(input), IPL_DEPTH_8U, 1);
		cvCvtColor(input, img_gray_s, CV_BGR2GRAY);
	//	cvThreshold(img_gray_s, img_gray_s, 250, 255, CV_THRESH_BINARY_INV);
		cvAdaptiveThreshold(img_gray_s, img_gray_s, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 21, 3);//�ֲ���ֵ
		//cvFlip(img_gray_s, NULL, 0);
		cvSaveImage(szName, img_gray_s);//����ͼƬ
		cvReleaseImage(&input);
		cvReleaseImage(&imgNo);
		
	}
	//cvFlip(imgSrc, NULL, 0);
	//Mat T = cvarrToMat(imgSrc);
	//resize(T, T, Size(2500, 900), 0, 0, CV_INTER_LINEAR);
	//imshow("name", T);

	

	//cvNamedWindow("ԭͼ");
//	cvSetWindowProperty("ԭͼ", 1,1);

	//cvShowImage("ԭͼ", imgSrc);//��ʾԭͼ
	cvWaitKey(0);
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&imgSrc); //cvReleaseImage����ֻ�ǽ�IplImage*�͵ı���ֵ��ΪNULL��
	//							��������������Ǵ��ڵĲ������ڴ��еĴ洢λ�ò��䡣
	cvReleaseImage(&img_gray);
	
	//
	cvDestroyAllWindows();
	//��������HighGUI����
	cvWaitKey(0);
	return 0;
}


