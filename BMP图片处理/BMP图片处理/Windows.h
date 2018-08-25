#pragma once
#include"windef.h"
#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType; // λͼ�ļ������ͣ�����Ϊ��BMP��
	DWORD bfSize; // λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
	WORD bfReserved1; // λͼ�ļ������֣�����Ϊ0
	WORD bfReserved2; // λͼ�ļ������֣�����Ϊ0
	DWORD bfOffBits; // λͼ���ݵ���ʼλ�ã��������λͼ�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
} BITMAPFILEHEADER;//�ýṹռ��14���ֽڡ�

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize; // ���ṹ��ռ���ֽ���
	LONG biWidth; // λͼ�Ŀ�ȣ�������Ϊ��λ
	LONG biHeight; // λͼ�ĸ߶ȣ�������Ϊ��λ
	WORD biPlanes; // Ŀ���豸��ƽ�������壬����Ϊ1
	WORD biBitCount;// ÿ�����������λ����������1(˫ɫ), 4(16ɫ)��8(256ɫ)��24(���ɫ)֮һ
	DWORD biCompression; // λͼѹ�����ͣ������� 0(��ѹ��),1(BI_RLE8ѹ������)��2(BI_RLE4ѹ������)֮һ
	DWORD biSizeImage; // λͼ�Ĵ�С�����ֽ�Ϊ��λ
	LONG biXPelsPerMeter; // λͼˮƽ�ֱ��ʣ�ÿ��������
	LONG biYPelsPerMeter; // λͼ��ֱ�ֱ��ʣ�ÿ��������
	DWORD biClrUsed;// λͼʵ��ʹ�õ���ɫ���е���ɫ��
	DWORD biClrImportant;// λͼ��ʾ��������Ҫ����ɫ��
} BITMAPINFOHEADER;//�ýṹռ��40���ֽڡ�

typedef struct tagRGBQUAD {
	BYTE rgbBlue;// ��ɫ������(ֵ��ΧΪ0-255)
	BYTE rgbGreen; // ��ɫ������(ֵ��ΧΪ0-255)
	BYTE rgbRed; // ��ɫ������(ֵ��ΧΪ0-255)
	BYTE rgbReserved;// ����������Ϊ0
} RGBQUAD;

typedef struct tagBITMAPINFO {
	BITMAPINFOHEADER bmiHeader; // λͼ��Ϣͷ
	RGBQUAD bmiColors[1]; // ��ɫ��
} BITMAPINFO;
#pragma pack(pop)