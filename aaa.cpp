
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
const char *pstrSrcWindowsTitle = "原图";
const char *pstrDestWindowsTitle_1 = "对原图腐蚀之后";
const char *pstrDestWindowsTitle_2 = "对原图膨胀之后";
const char *pstrDestWindowsTitle_3 = "对腐蚀过的图片作膨胀";

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

	//filename ：要被读入的文件的文件名(包括后缀)；	//flags ：指定读入图像的颜色和深度：
	//指定的颜色可以将输入的图片转为3通道(CV_LOAD_IMAGE_COLOR),
	//	单通道(CV_LOAD_IMAGE_GRAYSCALE),
	//或者保持不变(CV_LOAD_IMAGE_ANYCOLOR)。
	IplImage* img_gray = cvCreateImage(cvGetSize(imgSrc), IPL_DEPTH_8U, 1);

	
	

	cvCvtColor(imgSrc, img_gray, CV_BGR2GRAY);//转成灰色
	//cvFlip(img_gray, NULL, 0);

	//cvNamedWindow("灰度图像");//显示灰度图像
	//cvShowImage("灰度图像", img_gray);


//	cvSmooth(img_gray, img_gray, CV_MEDIAN, 3, 3);//中值模糊
//	cvShowImage("中值模糊", img_gray);
	
	

	cvErode(img_gray, img_gray, NULL, 1);//腐蚀处理，并显示  
	//cvShowImage(pstrDestWindowsTitle_1, img_gray);


	//cvDilate(img_gray, img_gray, NULL, 1);//膨胀处理，并显示  次数  
	//cvShowImage(pstrDestWindowsTitle_2, img_gray);
	//cvThreshold(img_gray, img_gray,230, 255, CV_THRESH_BINARY_INV);//全局阈值
	cvAdaptiveThreshold(img_gray, img_gray,255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV,21,3);//局部阈值
	
	

	
	//cvDilate(img_gray, img_gray, NULL, 1);//膨胀处理，并显示  次数  
//	cvShowImage(pstrDestWindowsTitle_2, img_gray);


	CvSeq* contours = NULL;
	CvMemStorage* storage = cvCreateMemStorage(0);
	
	int count = cvFindContours(img_gray, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL);
	
	//printf("个数：%d", idx);
	char szName[56] = { 0 };
	int tempCount = 0;
	int x = 0;
	int y = 0;
	for (CvSeq* c = contours; c != NULL; c = c->h_next) {
		CvRect rc = cvBoundingRect(c, 0);
		//CvRect 包含4个数据成员，x,y,width,height,
		//通过定义矩形左上角坐标和矩形的宽和高来确定一个矩形。
		//printf("id %d 宽：%d 高：%d\n", idx, rc.width, rc.height);
		if (rc.width<10 || rc.height<10 || rc.width>500 || rc.height>500)
		{
			continue;    // 这里可以根据轮廓的大小进行筛选
		}
		//画圈圈
//		cvDrawRect(imgSrc, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 255, 255));//CV_RGB(255, 0, 0)红
		IplImage* imgNo = cvCreateImage(cvSize(rc.width, rc.height), IPL_DEPTH_8U, 3);
		cvSetImageROI(imgSrc, rc);
		//基于给定的矩形设置图像的ROI（感兴趣区域
		//imgSrc只显示rc标识的一部分
		cvCopy(imgSrc, imgNo);
		//这个时候imgSrc指示标识的部分，将他进行拷贝
		cvResetImageROI(imgSrc);
		//cvResetImageROI(img1);之后，img1指示原来的图像信息
		
		x = rc.x;
		y = rc.y;
		y = y / 10 * 10;

		sprintf(szName, "/opt/deep_ocr/img/%d_%d_%d.png", x,y,idx++);
		//	cvNamedWindow(szName);
		//cvNamedWindow
		Mat M = cvarrToMat(imgNo);
		resize(M, M, Size(50, 50), 0, 0, CV_INTER_LINEAR);
		//如果想切割出来的图像从左到右排序，或从上到下，可以比较rc.x,rc.y;
		//cvShowImage(szName, imgNo);
		//	imshow(szName, M);
		//将图像贴到空白的图像上去
		Mat imageROI;
		Mat black = imread("/opt/deep_ocr/q.png");
		imageROI = black(Rect(10, 10, M.cols, M.rows));
		M.copyTo(imageROI);


		IplImage imgTmp = black;
		IplImage *input = cvCloneImage(&imgTmp);
		IplImage* img_gray_s = cvCreateImage(cvGetSize(input), IPL_DEPTH_8U, 1);
		cvCvtColor(input, img_gray_s, CV_BGR2GRAY);
	//	cvThreshold(img_gray_s, img_gray_s, 250, 255, CV_THRESH_BINARY_INV);
		cvAdaptiveThreshold(img_gray_s, img_gray_s, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 21, 3);//局部阈值
		//cvFlip(img_gray_s, NULL, 0);
		cvSaveImage(szName, img_gray_s);//保存图片
		cvReleaseImage(&input);
		cvReleaseImage(&imgNo);
		
	}
	//cvFlip(imgSrc, NULL, 0);
	//Mat T = cvarrToMat(imgSrc);
	//resize(T, T, Size(2500, 900), 0, 0, CV_INTER_LINEAR);
	//imshow("name", T);

	

	//cvNamedWindow("原图");
//	cvSetWindowProperty("原图", 1,1);

	//cvShowImage("原图", imgSrc);//显示原图
	cvWaitKey(0);
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&imgSrc); //cvReleaseImage函数只是将IplImage*型的变量值赋为NULL，
	//							而这个变量本身还是存在的并且在内存中的存储位置不变。
	cvReleaseImage(&img_gray);
	
	//
	cvDestroyAllWindows();
	//销毁所有HighGUI窗口
	cvWaitKey(0);
	return 0;
}


