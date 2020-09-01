#! /usr/bin/env/ python3
import rospy
from std_msgs.msg import Float32MultiArray
from motor_positions.msg import positionArray


global publisher = rospy.Publisher('converted_positions', Float32MultiArray, queue_size=10)


def matlab_conversion(msg){
        pass
        }

rospy.init_node('matlab_conversion', anonymous=True)

subscriber = rospy.Subscriber('matlab_conversion', positionArray, matlab_conversion)

rospy.spin()




