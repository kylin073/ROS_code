#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import Twist


def control_move(x_flag, z_flag):
    """ 
        this fun is used to control robot
        input: 
                x_flag: the linear_x position
                z_flag: the angular_z position
        output:
                publish to move robot
    """
    cmd = Twist()
    #pub = rospy.Publisher('turtle1/cmd_vel', Twist)
    pub = rospy.Publisher('/cmd_vel', Twist)
    cmd.linear.x = x_flag
    cmd.angular.z = z_flag
    pub.publish(cmd)


def position_callback(msg):
    """
        this fun is callback about the Opencv topic, in view window,
            move right the robot goforwad, move left the robot goback, 
            move close the robot turnright, move away the robot turnleft.
        input:
                msg: the Opencv massage about the face identifition
    """

    position_x = msg.data[0]
    #rospy.loginfo(position_x)
    position_y = msg.data[2]
    #rospy.loginfo(position_y)

    if (int(position_x) >= 50 & int(position_x) <= 350 
        & int(position_y) >= 100 & int(position_y) <= 350):
        if int(position_x) > 300:
            rospy.loginfo("forwad")
            control_move(0.5,0)
        elif int(position_x) < 150:
            control_move(-0.5,0)
            rospy.loginfo("back")
        elif int(position_y) > 250:
            rospy.loginfo("turnleft")
            control_move(0,0.5)
        elif int(position_y) < 180:
            control_move(0,-0.5)
            rospy.loginfo("turnright")
        else:
            control_move(0,0)


def position():
    """this is ros init function"""
    rospy.init_node('hm_subscriber', anonymous=True)
    rospy.Subscriber('/image_position', Float32MultiArray, position_callback)
    rospy.spin()

if __name__ == '__main__':
    position()   

