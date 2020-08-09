#include <iostream>		 
#include <opencv/highgui.h>					// high-level graphical user interface library
#include "opencv2/imgproc/imgproc.hpp"		
#include <opencv2/opencv.hpp>



int main()
{
    // get original image.
    cv::Mat originalImage = cv::imread("road.png");
    cv::imshow("original image", originalImage);
    
    // perspective image.
    cv::Mat perspectiveImage;
    // perspective transform
    cv::Point2f objectivePoints[6], imagePoints[6];
    
    // original image points.
    imagePoints[0].x = 10.0; imagePoints[0].y = 457.0;
    imagePoints[1].x = 395.0; imagePoints[1].y = 291.0;
    imagePoints[2].x = 624.0; imagePoints[2].y = 291.0;
    imagePoints[3].x = 1000.0; imagePoints[3].y = 457.0;
    imagePoints[4].x = 750.0; imagePoints[3].y = 457.0;
    imagePoints[5].x = 350.0; imagePoints[3].y = 457.0;
    
    // objective points of perspective image.
    // move up the perspective image : objectivePoints.y - value .
    // move left the perspective image : objectivePoints.x - value.
    double moveValueX = 0.0;
    double moveValueY = 0.0;
    
    /*
    objectivePoints[0].x = 46.0 + moveValueX; objectivePoints[0].y = 920.0 + moveValueY;
    objectivePoints[1].x = 46.0 + moveValueX; objectivePoints[1].y = 100.0 + moveValueY;
    objectivePoints[2].x = 600.0 + moveValueX; objectivePoints[2].y = 100.0 + moveValueY;
    objectivePoints[3].x = 600.0 + moveValueX; objectivePoints[3].y = 920.0 + moveValueY;
    */ 

    objectivePoints[0].x = 0.0 + moveValueX; objectivePoints[0].y = 899.0 + moveValueY;
    objectivePoints[1].x = 0.0 + moveValueX; objectivePoints[1].y = 0.0 + moveValueY;
    objectivePoints[2].x = 499.0 + moveValueX; objectivePoints[2].y = 0.0 + moveValueY;
    objectivePoints[3].x = 499.0 + moveValueX; objectivePoints[3].y = 899.0 + moveValueY;
    objectivePoints[4].x = 299.0 + moveValueX; objectivePoints[3].y = 899.0 + moveValueY;
    objectivePoints[5].x = 199.0 + moveValueX; objectivePoints[3].y = 899.0 + moveValueY;


    cv::Mat transform = cv::getPerspectiveTransform(objectivePoints, imagePoints);
    std::cout << transform << std::endl;
    std::cout << originalImage.rows << " " << originalImage.cols << std::endl;

    // perspective.
    cv::warpPerspective(    originalImage,
                            perspectiveImage,
                            transform,
                            //cv::Size(originalImage.rows, originalImage.cols),
                            cv::Size(500, 900),     // size of the new image 
                            cv::INTER_LINEAR | cv::WARP_INVERSE_MAP);
    cv::imshow("perspective image", perspectiveImage);
    cvWaitKey(0);
    cv::imwrite("perspectiveImage.png", perspectiveImage); // save perspectiveImage 
    return 0;
}
