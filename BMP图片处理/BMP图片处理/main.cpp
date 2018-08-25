#include<iostream>
#include"Windows.h"
#include"stdio.h"
#include <string.h>       
#include <malloc.h>  
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<time.h>//ʱ�����ͷ�ļ����������к�������ͼ�����ٶ�  
using namespace std;

unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��
int bmpWidth;//ͼ��Ŀ�
int bmpHeight;//ͼ��ĸ�
RGBQUAD *pColorTable;//��ɫ��ָ��
int biBitCount;//ͼ������

bool readBmp(char *bmpName)//ʵ��BMP�ļ��Ķ�ȡ����
{
	//�����ƶ���ʽ��ָ����ͼ���ļ�
	FILE *fp = fopen(bmpName, "rb");
	if (fp == 0) return 0;

	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;

	//�������������ͼ��ÿ��������ռ���ֽ������������ĵı�����
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;

	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
	if (biBitCount == 8) {
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);

	}

	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	pBmpBuf = new unsigned char[lineByte*bmpHeight];
	fread(pBmpBuf, 1, lineByte*bmpHeight, fp);

	//�ر��ļ�
	fclose(fp);
	return 1;
}

//ʵ��BMP�ļ���д����
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{
	//���λͼ����ָ��Ϊ0,��û�����ݴ���,��������
	if (!imgBuf)  return 0;
	//��ɫ���С,���ֽ�Ϊ��λ,�Ҷ�ͼ����ɫ��Ϊ1024�ֽ�,��ɫͼ����ɫ���СΪ0 
	int colorTablesize = 0;
	if (biBitCount == 8)  colorTablesize = 1024;
	//���洢ͼ������ÿ���ֽ���Ϊ4�ı���
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	//�Զ�����д�ķ�ʽ���ļ�
	FILE *fp = fopen(bmpName, "wb");
	if (fp == 0) return 0;
	//����λͼ�ļ�ͷ�ṹ����,��д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp����
							 //bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	//bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��
	fileHead.bfOffBits = 54 + colorTablesize;
	//д�ļ�ͷ���ļ�
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	//����λͼ��Ϣͷ�ṹ����,��д��Ϣͷ��Ϣ
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
	//дλͼ��Ϣͷ���ڴ�
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//����Ҷ�ͼ��,����ɫ��,д���ļ�
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	//дλͼ���ݽ��ļ�
	fwrite(imgBuf, height*lineByte, 1, fp);
	//�ر��ļ�
	fclose(fp);
	return 1;
}

//ͼƬ�ü�
void image_cut()
{
	unsigned char *imagedata = NULL; //��̬����洢ԭͼƬ��������Ϣ�Ķ�ά����
	unsigned char *imagedataCut = NULL;//��̬����洢�ü����ͼƬ��������Ϣ�Ķ�ά����
	char readPath[] = "�ֻ�.bmp";
	readBmp(readPath);
	imagedata = pBmpBuf;
	//===========================================ͼƬ�ü�����====================================================//
	int leftdownx, leftdowny, rightupx, rightupy;/////�û�������ֵ
	int Rleftdownx, Rleftdowny, Rrightupx, Rrightupy;/////ת����ʵ�ʿ���ʹ����ֵ
	cout << "������Ҫ�ü��ľ�����������½Ǻ����Ͻǵ����꣨�����ĸ�����ֵ����50 50 300 300):" << endl;
	cin >> leftdownx;
	cin >> leftdowny;
	cin >> rightupx;
	cin >> rightupy;
	//------------------------���û�����ľ��ο��޶���ԭͼ����--------------------------------//
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
	CutHeight = Rrightupy - Rleftdowny;////���ο�ʵ�ʸ߶�

	int lineByte2 = (CutWidth * biBitCount / 8 + 3) / 4 * 4;//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
	imagedataCut = new unsigned char[lineByte2 * CutHeight];
	//---------------------------ԭʼͼ����������ָ���ƶ������ο�����½ǡ�-------------------------------------------//

	imagedata = imagedata + (Rleftdowny)*bmpWidth * 3;

	//----------------------------�ü�����������ȡ-------------------------------------------//
	for (int i = 0; i < CutHeight; i++)
	{
		for (int j = 0; j < CutWidth; j++)
			for (int k = 0; k < 3; k++)
				*(imagedataCut + i * lineByte2 + j * 3 + k) = *(imagedata + i * bmpWidth * 3 + j * 3 + k + Rleftdownx * 3);////��ʽ��һ��Ҫע��д������Ҫ��ע���ά����ָ����÷���

	}

	char writePath[] = "�ü��ֻ�.bmp";
	saveBmp(writePath, imagedataCut, CutWidth, CutHeight, biBitCount, pColorTable);
	printf("�ü��任��ɣ���鿴bmp�ļ���\n\n");

	//�ͷ��ڴ�
	//delete[] imagedata;///�����ͷ�imagedata�����滹�����ݡ�
	delete[] imagedataCut;
}

//��Ҷ���˾�
void byc_mirror()
{
	//����ָ��BMP�ļ����ڴ�
	char readPath[] = "�ֻ�.bmp";
	readBmp(readPath);
	//���ͼ�����Ϣ
	printf("width=%d,height=%d, biBitCount=%d\n", bmpWidth, bmpHeight, biBitCount);
	//��Ҷ��
	//ѭ������,ͼ�������
	int i, j;
	//ÿ���ֽ���
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//ѭ������,��Բ�ɫͼ��,����ÿ���ص���������
	int k;
	if (biBitCount == 8) {//���ڻҶ�ͼ��
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
	else if (biBitCount == 24) {//��ɫͼ��
		for (i = 0;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j = j++) {
				for (k = 0;k<3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
		for (i = 1;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j ++) {
				for (k = 0;k<3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
		for (i = 2;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j++) {
				for (k = 0;k<3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
		for (i = 3;i<bmpHeight;i = i + 8) {
			for (j = 0;j<bmpWidth;j++) {
				for (k = 0;k<3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
	}
	//��ͼ�����ݴ���
	char writePath[] = "��Ҷ���ֻ�.bmp";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//���������,pBmpBuf��pColorTable��ȫ�ֱ���,���ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
}

//�����˾�
void my_mirror()
{
	//����ָ��BMP�ļ����ڴ�
	char readPath[] = "�ֻ�.bmp";
	readBmp(readPath);
	//���ͼ�����Ϣ
	printf("width=%d,height=%d, biBitCount=%d\n", bmpWidth, bmpHeight, biBitCount);
	//��Ҷ��
	//ѭ������,ͼ�������
	int i, j;
	//ÿ���ֽ���
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//ѭ������,��Բ�ɫͼ��,����ÿ���ص���������
	int k;
	if (biBitCount == 8) {//���ڻҶ�ͼ��
		for (i = bmpHeight * 4 / 7;i < bmpHeight * 4 / 5;i++) {
			for (j = bmpHeight / 4;j < bmpWidth * 3 / 4;j++) {
				*(pBmpBuf + i * lineByte + j) = 0;
			}
		}
	}
	else if (biBitCount == 24) {//��ɫͼ��
		for (i = bmpHeight * 4 / 7;i < bmpHeight * 4 / 5;i++) {
			for (j = bmpHeight / 4;j < bmpWidth * 3 / 4;j++) {
				for (k = 0;k < 3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
					*(pBmpBuf + i * lineByte + j * 3 + k) = 0;
			}
		}
	}
	char writePath[] = "�����ֻ�.bmp";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//���������,pBmpBuf��pColorTable��ȫ�ֱ���,���ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
}

void main() {
	byc_mirror();
	my_mirror();
	image_cut();
}