#! /usr/bin/env python3
import rospy
from motor_positions.msg import controlTable
from roboticstoolbox import mstraj
import numpy as np
from math import pi, ceil
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
a = [0.62, 0.86, 0.70, 0.61]

test = np.array(leg_ikine(1.5, 0, 0, -pi/2, -1, a))

zeros = np.array(
        [0, 0, 0, 0],
        )
path = np.row_stack((zeros, test))
# out = mstraj(path, dt=0.2, tacc=0.5, tsegment=[1])
pdb.set_trace()
move_msg = controlTable()

for move in path:
    # pdb.set_trace()
    for count, via in enumerate(move):
        move_msg.dest = count + 10
        move_msg.command_id = 0
        move_msg.value = ceil(radstoRaw(via))
        # print(move_msg.value)

        rospy.loginfo(move_msg)
        pub.publish(move_msg)
    sleep(0.1)



