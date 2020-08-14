#! /usr/bin/env python3
import rospy
from motor_positions.msg import controlTable
from roboticstoolbox import mstraj
import numpy as np
import math
import pdb
from time import sleep

# from std_msgs.msg import String

def radstoRaw(rads):
    raw = rads/ 0.00153589
    raw += 2048
    return(raw)

rospy.init_node('trajectories', anonymous=True)
pub = rospy.Publisher("dynamixel_control", controlTable, queue_size=100)
rate = rospy.Rate(10) # 10hz
msg = controlTable()

path = np.array([
        [0, -0.4401, -0.6496, -0.7019],
        [0, 0, 0, 0],
        [0, 0.4401, 0.6496, 0.7019]
        ])


out = mstraj(path, dt=0.2, tacc=0.5, tsegment=[1, 1])
# pdb.set_trace()
for i in range(10, 14):
    move_msg = controlTable()
    move_msg.dest = i
    move_msg.command_id = 2
    move_msg.value = 500
    rospy.loginfo(move_msg)
    pub.publish(move_msg)
    sleep(2)

pdb.set_trace()
for move in out.q:
    # pdb.set_trace()
    for count, via in enumerate(move):
        move_msg.dest = count + 10
        move_msg.command_id = 2
        move_msg.value = 0
        # print(move_msg.value)

        rospy.loginfo(move_msg)
        pub.publish(move_msg)
    sleep(0.1)


