/*************************************************************************
	> File Name: cxx_image.cpp
	> Author: 
	> Mail: 
	> Created Time: Fr 17 Jan 2020 11:07:42 CET
 ************************************************************************/

#include <libcouchbase/couchbase++.h>
#include <libcouchbase/couchbase++/views.h>
#include <libcouchbase/couchbase++/query.h>
#include <libcouchbase/couchbase++/endure.h>
#include <libcouchbase/couchbase++/logging.h>
//using namespace Couchbase;

#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
//using namespave cv;

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
//using namespace std;

#include<assert.h>
#include "base64.h"

#include<nlohmann/json.hpp>
using json = nlohmann::json;


static void storeImage(Couchbase::Client *client_handle_ptr)
{
    // read image 326.6KB 
    cv::Mat originImage = cv::imread("originImage.png", CV_LOAD_IMAGE_COLOR);
    cv::imshow("origin image", originImage);
    std::cout << "rows: " << originImage.rows << ", cols: " << originImage.cols << std::endl;

    // encode image to binary  
    std::vector<uchar> img_encode_data;
    cv::imencode(".png", originImage, img_encode_data);
    std::string img_encode_str(img_encode_data.begin(), img_encode_data.end());

    // encode binary to base64 
    std::string img_base64_str;
    Base64::Encode(img_encode_str, &img_base64_str);

    // json 
    json originImage_json;
    originImage_json["base64"] = img_base64_str;

    float centroid_vec[3] = {1.0,2.0,3.0}; 
    originImage_json["centroid"] = centroid_vec; 


    std::string value_string = originImage_json.dump();

    // item upsert 
    std::string key("originImage_base64_str");  
    auto sres = client_handle_ptr->upsert(key, value_string);   

    // store status
    std::cout << "Store status: cas = " << std::hex << sres.cas() << std::endl;
   
    cvWaitKey(0); //放到程序最后，便可以等上面的程序都执行结束，并同时一直显示图像
}

/*
    // image to array 
    std::vector<uchar> array_origin(originImage.rows*originImage.cols*originImage.channels()); // cv::mat to array, size of array: rows*cols*channels  
    //std::cout << originImage.isContinuous() << std::endl;
    if(originImage.isContinuous()) // check if the image mat is continuous 
    {
        array_origin.assign(originImage.data, originImage.data + originImage.total()*originImage.channels());
    }
    else
    {
        for(int i=0;i<originImage.rows;i++)
        {
            array_origin.insert(array_origin.end(), originImage.ptr<uchar>(i), originImage.ptr<uchar>(i) + originImage.cols*originImage.channels());
        }
    }
*/ 

static void getImage(Couchbase::Client *client_handle_ptr)
{
    // receive from couchbase 
    std::string key("originImage_base64_str");
    auto gres = client_handle_ptr->get(key);
    std::cout << "Receiving status for originImage_base64_str: " << gres.status() << std::endl;
    if( not gres.status())
    {
        exit(0);
    }
    std::string value_string = gres.value();
    json originImage_json = json::parse(value_string);
    std::string img_base64_str = originImage_json["base64"];

    // decode base64 to binary
    std::string img_encode_str;
    Base64::Decode(img_base64_str, &img_encode_str);

    // decode binary to image
    cv::Mat img_decode;
    std::vector<uchar> img_decode_data(img_encode_str.begin(), img_encode_str.end());
    img_decode = cv::imdecode(img_decode_data, CV_LOAD_IMAGE_COLOR);

    // display img_decode
    cv::imshow("img_decode", img_decode);

    // save img_decode 
    cv::imwrite("img_decode.png", img_decode);
    
    // write base64 to file 
    std::ofstream out;
    out.open("img_base64_str.txt", std::ios::out | std::ios::trunc);
    out << img_base64_str << std::endl;
    out.close();
    
    cvWaitKey(0);
}

int main(int argc, const char **argv)
{
    // connect options
    std::string connstr("couchbase://localhost/bucket-test");
    Couchbase::Client client_handle(connstr, "shan1123", "fog-ws");
    Couchbase::Client *client_handle_ptr = &client_handle; 

    // connect()
    Couchbase::Status connect_status = client_handle.connect();

    // check error
    if(!connect_status.success())
    {
        std::cout << "Couldn't connect to '" << connstr << "'. " << std::endl;
        std::cout << "Reason: " << connect_status << std::endl;
        exit(EXIT_FAILURE);
    }

    // storeImage()
    storeImage(client_handle_ptr);

    // get Image()
    getImage(client_handle_ptr);

    return 0;
}

