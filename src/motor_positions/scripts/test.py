#! /usr/bin/env python3
import rospy
# from std_msgs.msg import String
from motor_positions.msg import controlTable

rospy.init_node('test', anonymous=True)
pub = rospy.Publisher("dynamixel_control", controlTable, queue_size=10)
test = controlTable()
test.motor_id = 1
test.command_id = 58
test.value = 100
while True:
    pub.publish(test)
