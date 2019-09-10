#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <turtlesim/Spawn.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h"
#include <iostream>
using namespace std;



int main(int argc, char **argv)
{
    string turtle_name;
    float turtle_angular_z;
    float turtle_linear_x;
    
    ros::init(argc, argv, "control_turtle_circle");
    ros::NodeHandle n;

    cout << "输入已有海龟名字";
    cin >> turtle_name;
    cout << "输入海龟的角速度和线速度";
    cin >> turtle_angular_z >> turtle_linear_x;


    ros::Publisher turtle_pub = n.advertise<geometry_msgs::Twist>(turtle_name+"/cmd_vel", 10);
    ros::Rate rate=(10.0);
    
    while (ros::ok())
    {
        
        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z = turtle_angular_z;
        vel_msg.linear.x = turtle_linear_x;
        turtle_pub.publish(vel_msg);

        ros::spinOnce();
        rate.sleep();

    }
    


    
    return 0;
}

