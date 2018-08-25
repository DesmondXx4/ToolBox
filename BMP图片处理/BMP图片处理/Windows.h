#pragma once
#include"windef.h"
#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType; // 位图文件的类型，必须为“BMP”
	DWORD bfSize; // 位图文件的大小，以字节为单位
	WORD bfReserved1; // 位图文件保留字，必须为0
	WORD bfReserved2; // 位图文件保留字，必须为0
	DWORD bfOffBits; // 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
} BITMAPFILEHEADER;//该结构占据14个字节。

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize; // 本结构所占用字节数
	LONG biWidth; // 位图的宽度，以像素为单位
	LONG biHeight; // 位图的高度，以像素为单位
	WORD biPlanes; // 目标设备的平面数不清，必须为1
	WORD biBitCount;// 每个像素所需的位数，必须是1(双色), 4(16色)，8(256色)或24(真彩色)之一
	DWORD biCompression; // 位图压缩类型，必须是 0(不压缩),1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一
	DWORD biSizeImage; // 位图的大小，以字节为单位
	LONG biXPelsPerMeter; // 位图水平分辨率，每米像素数
	LONG biYPelsPerMeter; // 位图垂直分辨率，每米像素数
	DWORD biClrUsed;// 位图实际使用的颜色表中的颜色数
	DWORD biClrImportant;// 位图显示过程中重要的颜色数
} BITMAPINFOHEADER;//该结构占据40个字节。

typedef struct tagRGBQUAD {
	BYTE rgbBlue;// 蓝色的亮度(值范围为0-255)
	BYTE rgbGreen; // 绿色的亮度(值范围为0-255)
	BYTE rgbRed; // 红色的亮度(值范围为0-255)
	BYTE rgbReserved;// 保留，必须为0
} RGBQUAD;

typedef struct tagBITMAPINFO {
	BITMAPINFOHEADER bmiHeader; // 位图信息头
	RGBQUAD bmiColors[1]; // 颜色表
} BITMAPINFO;
#pragma pack(pop)