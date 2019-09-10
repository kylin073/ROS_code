#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <turtlesim/Spawn.h>
#include <geometry_msgs/Twist.h>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "homework_turtlespawn");
    ros::NodeHandle n;
    ros::service::waitForService("spawn");
    ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;
    srv.request.x = 5;
    srv.request.y = 5;
    srv.request.name = "turtle2";
    add_turtle.call(srv);
    ROS_INFO("The turtle2 has been spawn!");


    return 0;
}