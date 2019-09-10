#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <turtlesim/Spawn.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/String.h"
#include <iostream>
using namespace std;



int main(int argc, char** argv)
{
    string turtle_name[10];
    int turtle_num;
    //float turtle_x[10];
    //float turtle_y[10];
    int i;

    ros::init(argc, argv, "create_turtle_client");
    ros::NodeHandle node;

    ros::service::waitForService("spawn");
    ros::ServiceClient turtle_client = node.serviceClient<turtlesim::Spawn>("spawn");
    
    /*cout << "输入海龟名字";
    cin >> turtle_name;
    cout << "输入海龟的位置";
    cin >> turtle_x  >> turtle_y ;*/

    cout << "希望创建海龟的个数(小于10个)";
    cin >> turtle_num;
    for (size_t i = 0; i < turtle_num; i++)
   {
        cout << "请输入海龟名字";
        cin >> turtle_name[i];
        
        //cout << "输入海龟的位置";
        //cin >> turtle_x[i]  >> turtle_y[i] ;
        turtlesim::Spawn srv[10];
        srv[i].request.x = i+1;
        srv[i].request.y = i+1;
        srv[i].request.name = turtle_name[i];
        turtle_client.call(srv[i]);
    
    
   }
    
  
  return 0;
};

