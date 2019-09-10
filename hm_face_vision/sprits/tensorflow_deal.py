#!/usr/bin/env python


import rospy
from std_msgs.msg import String , Header
from vision_msgs.msg import Detection2D, Detection2DArray, ObjectHypothesisWithPose
from geometry_msgs.msg import Twist
import object_detection


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

  
def trcakcallback(data):
    #rospy.loginfo(data.detections[0].results[0].id)
    #id_num = data.detections[0].results[0].id
    if int(data.detections[0].results[0].id) == 47:
        x_position = data.detections[0].bbox.center.x
        y_position = data.detections[0].bbox.center.y
        #rospy.loginfo("x position --> %s" % x_position)
        #rospy.loginfo("y position --> %s" % y_position)
        if (int(x_position) > 90 & int(x_position) <=400 
                 & int(y_position) > 200 & int(y_position) < 600):         
            if int(y_position) <= 400:
                if int(x_position) > 300:
                    rospy.loginfo("forwad")
                    control_move(0.5,0)
                elif int(x_position) < 240:
                    rospy.loginfo("back")
                    control_move(-0.5,0)
                else:
                    control_move(0,0)
            elif int(y_position) > 450:
                if int(x_position) > 200:
                    rospy.loginfo("turnleft")
                    control_move(0,0.5)
                elif int(x_position) < 200:
                    rospy.loginfo("turnright")
                    control_move(0,-0.5)
                else:
                    control_move(0,0)
    else:
        control_move(0,0)  


def position():
    rospy.init_node('track_node')
    rospy.Subscriber("/objects",Detection2DArray, trcakcallback)
    rospy.spin()    

if __name__ == '__main__':
    position()
