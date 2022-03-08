#include "opencv_hw/ColorFilter.h"

using namespace std;
using namespace cv;


void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    //showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {
    
    //  problem 1
   // imshow("colors",_frame);

   //  PROBLEM 2: B
   // imshow("colors", _chans[2]);

   // PROBLEM 2: R
   // imshow("colors", _chans[1]);

   // PROBLEM 2: G
   // imshow("colors", _chans[0]);

   // PROBLEM 3: Blue Subtraction
   //imshow("colors", _blueMask);
   
   
   // PROBLEM 3: Green Subtraction
   //imshow("colors", _greenMask);


   // PROBLEM 3: Red Subtraction
   //imshow("colors", _redMask);

    // PROBLEM 6: ALL THREE
    //imshow("colors", _totalColors);


}

void ColorFilter::findBlue() {
    Mat bMinusR;
    subtract(_chans[0], _chans[2], bMinusR);

    Mat thresh;
    threshold(bMinusR, thresh, 50, 255, cv::THRESH_BINARY);
    
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(   contourimage, contours, maxSizeContour, cv::Scalar(255,255,255),
                    cv::LineTypes::FILLED, 8, hierarchy );

    cv::Mat contourmask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( contourmask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy );
    
    cv::Mat blueCupImg;
    _frame.copyTo(blueCupImg, contourmask);
    _blueMask = blueCupImg;
}

void ColorFilter::findGreen() {
    Mat GMinusB;
    subtract(_chans[1], _chans[0], GMinusB);

    Mat thresh;
    threshold(GMinusB, thresh, 50, 255, cv::THRESH_BINARY);
    
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(   contourimage, contours, maxSizeContour, cv::Scalar(255,255,255),
                    cv::LineTypes::FILLED, 8, hierarchy );

    cv::Mat contourmask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( contourmask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy );
    
    cv::Mat greenCupImg;
    _frame.copyTo(greenCupImg, contourmask);
    _greenMask = greenCupImg;



}

void ColorFilter::findRed() {
    Mat RMinusG;
    subtract(_chans[2], _chans[1], RMinusG);

    Mat thresh;
    threshold(RMinusG, thresh, 50, 255, cv::THRESH_BINARY);
    
    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0;
    for(int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if(contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    cv::Mat contourimage = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    drawContours(   contourimage, contours, maxSizeContour, cv::Scalar(255,255,255),
                    cv::LineTypes::FILLED, 8, hierarchy );

    cv::Mat contourmask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours( contourmask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy );
    
    cv::Mat redCupImg;
    _frame.copyTo(redCupImg, contourmask);
    _redMask = redCupImg;

}

void ColorFilter::findBGR() {
    Mat BGRMask;
    cv:: bitwise_or(_greenMask, _blueMask, BGRMask);
    cv:: bitwise_or(_redMask, BGRMask, BGRMask);
    _totalColors = BGRMask;
}


cv::Mat ColorFilter::getBlueImage() {
    return _blueMask;
}
cv::Mat ColorFilter::getGreenImage() {
    return _greenMask;
}
cv::Mat ColorFilter::getRedImage() {
    return _redMask;
}
cv::Mat ColorFilter::getBGRImage() {
    return _totalColors;
}