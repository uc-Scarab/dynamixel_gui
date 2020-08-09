#! /usr/bin/env python3
import rospy
from motor_positions.msg import controlTable
from roboticstoolbox import mstraj
import numpy as np
import math
import pdb
from time import sleep
from inv_kine import leg_ikine

# from std_msgs.msg import String

def radstoRaw(rads):
    raw = rads/ 0.00153589
    raw += 2048
    return(raw)

rospy.init_node('trajectories', anonymous=True)
pub = rospy.Publisher("dynamixel_control", controlTable, queue_size=60)
rate = rospy.Rate(10) # 10hz
msg = controlTable()



out = mstraj(path, dt=0.2, tacc=0.5, tsegment=[1])
# pdb.set_trace()
move_msg = controlTable()

for move in out.q:
    # pdb.set_trace()
    for count, via in enumerate(move):
        move_msg.motor_id = count + 1
        move_msg.command_id = 58
        move_msg.value = math.ceil(radstoRaw(via))
        # print(move_msg.value)

        rospy.loginfo(move_msg)
        pub.publish(move_msg)
    sleep(0.1)



