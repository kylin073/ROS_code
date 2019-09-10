#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
 
static const std::string OPENCV_WINDOW = "Image window";
 
class ImageConverter
{
   ros::NodeHandle n;
   image_transport::ImageTransport it;
   image_transport::Subscriber image_sub;
   image_transport::Publisher image_pub;
 
public:
   ImageConverter()
     : it(n)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub = it.subscribe("/usb_cam/image_raw", 1,
       &ImageConverter::imageCb, this);
    image_pub = it.advertise("cv_briage_image", 1);
 
    cv::namedWindow(OPENCV_WINDOW);
   }
 
  ~ImageConverter()
  {
     cv::destroyWindow(OPENCV_WINDOW);
  }
 
   void imageCb(const sensor_msgs::ImageConstPtr& msg)
   {
    cv_bridge::CvImagePtr cv_ptr;
     try
     {
       cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
     }
     catch (cv_bridge::Exception& e)
     {
       ROS_ERROR("cv_bridge exception: %s", e.what());
       return;
     }
 
     // Draw an example circle on the video stream
     if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
       cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));
 
     // Update GUI Window
     cv::imshow(OPENCV_WINDOW, cv_ptr->image);
     cv::waitKey(3);
 
     // Output modified video stream
     image_pub.publish(cv_ptr->toImageMsg());
   }
 };
   
  int main(int argc, char** argv)
  {
  ros::init(argc, argv, "image_converter");
   ImageConverter ic;
   ros::spin();
   return 0;
 }
