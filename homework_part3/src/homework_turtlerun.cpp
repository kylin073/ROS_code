#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>



void poseCallback(const turtlesim::PoseConstPtr &msg)
{
    //发布海龟的位置坐标
    ROS_INFO("the turtle position : (%f,%f)",msg->x,msg->y);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "homework_turtlerun");
    ros::NodeHandle n;
    //创建一个发布者和订阅者
    ros::Publisher turtle_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    ros::Subscriber turtle_sub = n.subscribe<turtlesim::Pose>("turtle1/pose",10,&poseCallback);

    ros::Rate rate=(10.0);
    
    while (ros::ok())
    {
        //让海龟进行圆周运动
        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z = 1;
        vel_msg.linear.x = 1;
        turtle_pub.publish(vel_msg);

        ros::spinOnce();
        rate.sleep();

    }
    


    
    return 0;
}
