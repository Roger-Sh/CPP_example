/*************************************************************************
	> File Name: image2base64.cpp
	> Author: 
	> Mail: 
	> Created Time: Di 21 Jan 2020 14:13:09 CET
 ************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
//using namespace std;

#include "base64.h"

#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
//using namespace cv;

void write( std::string encode_str,
            std::string fileName );
std::string read(std::string fileName);

std::string encode(std::string imageName);
cv::Mat decode( std::string encode_str);


int main()
{
    // encode image to base64 
    std::string image_base64_str = encode("originImage.png"); 
    
    // write base64_str 
    write(image_base64_str, "originImage_base64.txt");

    // decode base64 to image 
    cv::Mat img = decode(image_base64_str); 
    
    cv::imshow("decode", img);
    
    cvWaitKey(0);

    return 0;
}

// write encode_str to file 
void write( std::string encode_str,
            std::string fileName)
{
    std::ofstream out;
    out.open(fileName, std::ios::out | std::ios::trunc);
    out << encode_str << std::endl;
    out.close();
}

// read encode_str from file 
std::string read(std::string fileName)
{
    std::string encode_str;
    std::ifstream in;
    in.open(fileName, std::ios::in);
    in >> encode_str;
    in.close();
    return encode_str;
}

// encode image to binary and then to base64 
std::string encode(std::string imageName) 
{
    // read image 
    cv::Mat img;
    img = cv::imread(imageName);
    
    // check 
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return "Failed";
    }

    // image to binary 
    std::vector<uchar> img_data;
    cv::imencode(".png", img, img_data); // cv::imencode 
    std::string str_Encode(img_data.begin(), img_data.end());

    // binary to base64 
    std::string base64_str;
    Base64::Encode(str_Encode, &base64_str);
    return base64_str;
}

/*
bool imencode(const string& ext, InputArray img, vector& buf, const vector& params=vector())
//ext：  图片后缀名，如".jpg"或".png"
//img：  需要进行相关操作的图片
//buf：  输出二进制数据到该缓存。

//params：格式相关的参数
//params中的每个参数成对出现，即paramId_1, paramValue_1, paramId_2, paramValue_2, … ，当前支持如下参数：
//JPEG：压缩质量 ( CV_IMWRITE_JPEG_QUALITY )，从0到100（数值越高质量越好），默认值为95。
//PNG：  compression level ( CV_IMWRITE_PNG_COMPRESSION ) 从0到9。 数值越高，文件大小越小，压缩时间越长。默认值为3。
//PPM,  PGM, or PBM：二进制标志 ( CV_IMWRITE_PXM_BINARY )，0 或 1。默认值为1。
*/ 

// decode Base64 to binary and then to image 
cv::Mat decode( std::string encode_str)
{
    // decode base64 to binary 
    std::string decode_str;
    Base64::Decode(encode_str, &decode_str);

    // decode binary to image 
    std::vector<uchar> img_data(decode_str.begin(), decode_str.end());
    cv::Mat img = imdecode(cv::Mat(img_data), CV_LOAD_IMAGE_COLOR);
    return img;
}

