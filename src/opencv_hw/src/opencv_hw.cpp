#include <image_transport/image_transport.h>
#include <opencv_hw/ColorFilter.h>
#include <opencv_hw/ROSInterface.h>

int main(int argc, char** argv)
{

  ros::init(argc, argv, "image_converter");
  ROSInterface ic;

  ros::spin();
  return 0;
}