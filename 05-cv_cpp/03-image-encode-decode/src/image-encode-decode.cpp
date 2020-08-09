/*************************************************************************
	> File Name: image-encode-decode.cpp
	> Author: 
	> Mail: 
	> Created Time: Di 21 Jan 2020 16:32:33 CET
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
//using namespace std;

#include<opencv2/opencv.hpp>
//using namespace cv;



int main(int argc, char ** argv)
{
    // read image 
    cv::Mat img_encode = cv::imread("originImage.png", CV_LOAD_IMAGE_COLOR);

    // encode image 
    std::vector<uchar> img_encode_data;
    cv::imencode(".png", img_encode, img_encode_data);
    std::string img_encode_str(img_encode_data.begin(), img_encode_data.end());
    
    std::cout << img_encode_str << std::endl;

    // decode image_encode_str
    cv::Mat img_decode;
    std::vector<uchar> img_decode_data(img_encode_str.begin(), img_encode_str.end());
    img_decode = cv::imdecode(img_decode_data, CV_LOAD_IMAGE_COLOR);

    // display img_decode  
    cv::imshow("img_decode", img_decode);
    cvWaitKey(0);

    // save img_decode 
    cv::imwrite("originImage_decode.png", img_decode);

    return 0;
}




