# BMP图片处理——裁剪+简易马赛克   
班级：电气1608    
学号：U201611848   
姓名：陈田田
## 一、简介
本程序基于C++数字图像处理技术，能读取保存图片，对图片进行裁剪，利用像素点的颜色调整加马赛克，并在原图片的储存位置上保存图片副本。
## 二、基本框架与功能
### 1、图片读取与保存
由读函数readBmp（）和存函数saveBmp（）实现；
![](https://raw.githubusercontent.com/DesmondXx4/ToolBox/master/BMP%E5%9B%BE%E7%89%87%E5%A4%84%E7%90%86/BMP%E5%9B%BE%E7%89%87%E5%A4%84%E7%90%86/%E8%83%96%E8%99%8E.bmp)

### 2、图片裁剪
由裁剪函数image_cut（）实现；
![](https://raw.githubusercontent.com/DesmondXx4/ToolBox/master/BMP%E5%9B%BE%E7%89%87%E5%A4%84%E7%90%86/BMP%E5%9B%BE%E7%89%87%E5%A4%84%E7%90%86/%E8%A3%81%E5%89%AA%E8%83%96%E8%99%8E.bmp)

### 3、马赛克
马赛克功能是通过将不同位置的像素点调为黑色实现的，因此理论上可以达到多种样式。本程序主要提供了百叶窗、蒙眼play两种形式。分别由函数byc_mirror()和函数my_mirror()实现。
![](https://raw.githubusercontent.com/DesmondXx4/ToolBox/master/BMP%E5%9B%BE%E7%89%87%E5%A4%84%E7%90%86/BMP%E5%9B%BE%E7%89%87%E5%A4%84%E7%90%86/%E7%99%BE%E5%8F%B6%E7%AA%97%E8%83%96%E8%99%8E.bmp)
![](https://raw.githubusercontent.com/DesmondXx4/ToolBox/master/BMP%E5%9B%BE%E7%89%87%E5%A4%84%E7%90%86/BMP%E5%9B%BE%E7%89%87%E5%A4%84%E7%90%86/%E8%92%99%E7%9C%BC%E8%83%96%E8%99%8E.bmp
)
## 三、程序升级
### 1、该图片处理程序的功能都是通过不同的函数实现，在主程序统一调用。日后可以通过增加功能函数使该图片处理程序的功能更加强大。
### 2、对像素点的调整在色彩上也可以有更大的发展空间。
