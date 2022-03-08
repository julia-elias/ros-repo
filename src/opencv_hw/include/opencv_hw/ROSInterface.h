#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H


#include "opencv_hw/ColorFilter.h"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

class ROSInterface {
protected: 
    ros::NodeHandle _nh;
    image_transport::ImageTransport _it;
    image_transport::Subscriber _sub;
    image_transport::Publisher _red;
    image_transport::Publisher _blue;
    image_transport::Publisher _green;
    image_transport::Publisher _bgr;
    ColorFilter _cf;

public: 
    ROSInterface();
    ~ROSInterface();
    void imageCb(const sensor_msgs::ImageConstPtr& msg);

};

#endif