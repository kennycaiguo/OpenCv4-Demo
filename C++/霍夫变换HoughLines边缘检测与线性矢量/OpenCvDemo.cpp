﻿/*
OpenCv版本 opencv-4.5.5-vc14_vc15
内容：霍夫变换HoughLines边缘检测与线性矢量
博客：http://www.bilibili996.com/Course?id=3905534000171
作者：高仁宝
时间：2023.11
*/

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
    //【1】载入原始图和Mat变量定义   
    Mat srcImage = imread("../images/home.jpg");
    Mat midImage, dstImage;//临时变量和目标图的定义

    //【2】进行边缘检测和转化为灰度图
    Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测
    // opencv3：CV_GRAY2BGR
    // opencv4：COLOR_GRAY2BGR
    cvtColor(midImage, dstImage, COLOR_GRAY2BGR);//转化边缘检测后的图为灰度图

    //【3】进行霍夫线变换
    vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
    HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);

    //【4】依次在图中绘制出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        // opencv3：CV_AA
        // opencv4：LINE_AA
        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
    }

    //【5】显示原始图  
    imshow("【原始图】", srcImage);

    //【6】边缘检测后的图 
    imshow("【边缘检测后的图】", midImage);

    //【7】显示效果图  
    imshow("【效果图】", dstImage);

    waitKey(0);
    return 0;
}