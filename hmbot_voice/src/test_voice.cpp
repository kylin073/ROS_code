#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <turtlesim/Spawn.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h"
#include <iostream>
using namespace std;

geometry_msgs::Twist control(float x_flag,float z_flag)
{
    geometry_msgs::Twist control_msg;
    control_msg.linear.x = x_flag;
    control_msg.angular.z = z_flag;
    return control_msg;

}

int main(int argc, char **argv)
{
 
    
    ros::init(argc, argv, "control_turtle_circle");
    ros::NodeHandle n;
    int i=5;


    ros::Publisher turtle_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    ros::Rate rate=(10.0);
    
    while (i)
    {
        
        geometry_msgs::Twist vel_msg;
        vel_msg = control(-1,0);
        turtle_pub.publish(vel_msg);
        i--;

        //ros::spinOnce();
        rate.sleep();

    }
    


    
    return 0;
}
