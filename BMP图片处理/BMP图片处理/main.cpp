#include<iostream>
#include"Windows.h"
#include"stdio.h"
#include <string.h>       
#include <malloc.h>  
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<time.h>//时间相关头文件，可用其中函数计算图像处理速度  
using namespace std;

unsigned char *pBmpBuf;//读入图像数据的指针
int bmpWidth;//图像的宽
int bmpHeight;//图像的高
RGBQUAD *pColorTable;//颜色表指针
int biBitCount;//图像类型

bool readBmp(char *bmpName)//实现BMP文件的读取操作
{
	//二进制读方式打开指定的图像文件
	FILE *fp = fopen(bmpName, "rb");
	if (fp == 0) return 0;

	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//获取图像宽、高、每像素所占位数等信息
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;

	//定义变量，计算图像每行像素所占的字节数（必须是四的倍数）
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;

	//灰度图像有颜色表，且颜色表表项为256
	if (biBitCount == 8) {
		//申请颜色表所需要的空间，读颜色表进内存
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);

	}

	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf = new unsigned char[lineByte*bmpHeight];
	fread(pBmpBuf, 1, lineByte*bmpHeight, fp);

	//关闭文件
	fclose(fp);
	return 1;
}

//实现BMP文件的写操作
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{
	//如果位图数据指针为0,则没有数据传入,函数返回
	if (!imgBuf)  return 0;
	//颜色表大小,以字节为单位,灰度图像颜色表为1024字节,彩色图像颜色表大小为0 
	int colorTablesize = 0;
	if (biBitCount == 8)  colorTablesize = 1024;
	//待存储图像数据每行字节数为4的倍数
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	//以二进制写的方式打开文件
	FILE *fp = fopen(bmpName, "wb");
	if (fp == 0) return 0;
	//申请位图文件头结构变量,填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型
							 //bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	//bfOffBits是图像文件前3个部分所需空间之和
	fileHead.bfOffBits = 54 + colorTablesize;
	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	//申请位图信息头结构变量,填写信息头信息
	BITMAPINFOHEADER head;
	head.biBitCount = biBitCount;
	head.biClrImportant = 0;
	head.biClrUsed = 0;
	head.biCompression = 0;
	head.biHeight = height;
	head.biPlanes = 1;
	head.biSize = 40;
	head.biSizeImage = lineByte * height;
	head.biWidth = width;
	head.biXPelsPerMeter = 0;
	head.biYPelsPerMeter = 0;
	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//如果灰度图像,有颜色表,写入文件
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	//写位图数据进文件
	fwrite(imgBuf, height*lineByte, 1, fp);
	//关闭文件
	fclose(fp);
	return 1;
}

//图片裁剪
void image_cut()
{
	unsigned char *imagedata = NULL; //动态分配存储原图片的像素信息的二维数组
	unsigned char *imagedataCut = NULL;//动态分配存储裁剪后的图片的像素信息的二维数组
	char readPath[] = "胖虎.bmp";
	readBmp(readPath);
	imagedata = pBmpBuf;
	//===========================================图片裁剪处理====================================================//
	int leftdownx, leftdowny, rightupx, rightupy;/////用户输入数值
	int Rleftdownx, Rleftdowny, Rrightupx, Rrightupy;/////转换成实际可以使用数值
	cout << "请输入要裁剪的矩形区域的左下角和右上角的坐标（连续四个整数值，如50 50 300 300):" << endl;
	cin >> leftdownx;
	cin >> leftdowny;
	cin >> rightupx;
	cin >> rightupy;
	//------------------------将用户输入的矩形框限定在原图像中--------------------------------//
	if (leftdownx < 0 && leftdowny < 0)
	{
		Rleftdownx = 0;
		Rleftdowny = 0;
	}
	else if (leftdownx <= 0 && leftdowny >= 0)
	{
		Rleftdownx = 0;
		Rleftdowny = leftdowny;
	}
	else if (leftdownx >= 0 && leftdowny <= 0)
	{
		Rleftdownx = leftdownx;
		Rleftdowny = 0;
	}
	else if (leftdownx > 0 && leftdowny > 0)
	{
		Rleftdownx = leftdownx;
		Rleftdowny = leftdowny;
	}

	if (rightupx >= bmpWidth)
	{
		Rrightupx = bmpWidth;
	}
	else
	{
		Rrightupx = rightupx;
	}
	if (rightupy >= bmpHeight)
	{
		Rrightupy = bmpHeight;
	}
	else
	{
		Rrightupy = rightupy;
	}
	int CutWidth, CutHeight;
	CutWidth = Rrightupx - Rleftdownx;
	CutHeight = Rrightupy - Rleftdowny;////矩形框实际高度

	int lineByte2 = (CutWidth * biBitCount / 8 + 3) / 4 * 4;//灰度图像有颜色表，且颜色表表项为256
	imagedataCut = new unsigned char[lineByte2 * CutHeight];
	//---------------------------原始图像数据数组指针移动到矩形框的左下角。-------------------------------------------//

	imagedata = imagedata + (Rleftdowny)*bmpWidth * 3;

	//----------------------------裁剪区域数据提取-------------------------------------------//
	for (int i = 0; i < CutHeight; i++)
	{
		for (int j = 0; j < CutWidth; j++)
			for (int k = 0; k < 3; k++)
				*(imagedataCut + i * lineByte2 + j * 3 + k) = *(imagedata + i * bmpWidth * 3 + j * 3 + k + Rleftdownx * 3);////此式子一定要注意写法。主要是注意二维数组指针的用法。

	}

	char writePath[] = "裁剪胖虎.bmp";
	saveBmp(writePath, imagedataCut, CutWidth, CutHeight, biBitCount, pColorTable);
	printf("裁剪变换完成，请查看bmp文件。\n\n");

	//释放内存
	//delete[] imagedata;///不能释放imagedata，里面还有数据。
	delete[] imagedataCut;
}

//百叶窗滤镜
void byc_mirror()
{
	//读入指定BMP文件进内存
	char readPath[] = "胖虎.bmp";
	readBmp(readPath);
	//输出图像的信息
	printf("width=%d,height=%d, biBitCount=%d\n", bmpWidth, bmpHeight, biBitCount);
	//百叶窗
	//循环变量,图像的坐标
	int i, j;
	//每行字节数
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//循环变量,针对彩色图像,遍历每像素的三个分量
	int k;
	if (biBitCount == 8) {//对于灰度图像
		for (i = 0;i<bmpHeight ;i=i+8) {
			for (j = 0;j<bmpWidth;j++) {
				*(pBmpBuf + i * lineByte + j) = 0;
			}
		}
		for (i = 1;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j++) {
				*(pBmpBuf + i * lineByte + j) = 0;
			}
		}
		for (i = 2;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j++) {
				*(pBmpBuf + i * lineByte + j) = 0;
			}
		}
		for (i = 3;i<bmpHeight;i=i+8) {
			for (j = 0;j<bmpWidth;j++) {
				*(pBmpBuf + i * lineByte + j) = 0;
			}
		}
	}
	else if (biBitCount == 24) {//彩色图像
		for (i = 0;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j = j++) {
				for (k = 0;k<3;k++)//每像素RGB三个分量分别置0才变成黑色
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
		for (i = 1;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j ++) {
				for (k = 0;k<3;k++)//每像素RGB三个分量分别置0才变成黑色
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
		for (i = 2;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j++) {
				for (k = 0;k<3;k++)//每像素RGB三个分量分别置0才变成黑色
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
		for (i = 3;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j++) {
				for (k = 0;k<3;k++)//每像素RGB三个分量分别置0才变成黑色
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
	}
	//将图像数据存盘
	char writePath[] = "百叶窗胖虎.bmp";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//清除缓冲区,pBmpBuf和pColorTable是全局变量,在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
}

//蒙眼滤镜
void my_mirror()
{
	//读入指定BMP文件进内存
	char readPath[] = "胖虎.bmp";
	readBmp(readPath);
	//输出图像的信息
	printf("width=%d,height=%d, biBitCount=%d\n", bmpWidth, bmpHeight, biBitCount);
	//百叶窗
	//循环变量,图像的坐标
	int i, j;
	//每行字节数
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//循环变量,针对彩色图像,遍历每像素的三个分量
	int k;
	if (biBitCount == 8) {//对于灰度图像
		for (i = bmpHeight * 4 / 7;i < bmpHeight * 4 / 5;i++) {
			for (j = bmpHeight / 4;j < bmpWidth * 3 / 4;j++) {
				*(pBmpBuf + i * lineByte + j) = 0;
			}
		}
	}
	else if (biBitCount == 24) {//彩色图像
		for (i = bmpHeight * 4 / 7;i < bmpHeight * 4 / 5;i++) {
			for (j = bmpHeight / 4;j < bmpWidth * 3 / 4;j++) {
				for (k = 0;k < 3;k++)//每像素RGB三个分量分别置0才变成黑色
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
	}
	char writePath[] = "蒙眼胖虎.bmp";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//清除缓冲区,pBmpBuf和pColorTable是全局变量,在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
}

void main() {
	byc_mirror();
	my_mirror();
	image_cut();
}