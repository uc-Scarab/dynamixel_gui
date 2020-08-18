#! /usr/bin/env python3
import rospy
from motor_positions.msg import controlTable
from roboticstoolbox import mstraj
import numpy as np
from math import ceil
import pdb
from time import sleep

# from std_msgs.msg import String

def radstoRaw(rads):
    raw = rads/ 0.00153589
    raw += 2048
    return(ceil(raw))

rospy.init_node('trajectories', anonymous=True)
pub = rospy.Publisher("dynamixel_control", controlTable, queue_size=100)
rate = rospy.Rate(10) # 10hz
msg = controlTable()

path = np.array([
        [0, -0.4401, -0.6496, -0.7019],
        [0, 0, 0, 0],
        [0, 0.4401, 0.6496, 0.7019]
        ])

path2 = np.array([
        [0, 0.4401, 0.6496, 0.7019],
        [0, 0, 0, 0],
        [0, -0.4401, -0.6496, -0.7019]
        ])



def movetoTrajectories(path):
    move_msg = controlTable()

    out = mstraj(path, dt=0.2, tacc=0.5, tsegment=[1, 1])
    for move in out.q:
        for count, via in enumerate(move):
            move_msg.dest = count + 10
            move_msg.command_id = 0
            move_msg.value = ceil(radstoRaw(via))

            rospy.loginfo(move_msg)
            pub.publish(move_msg)

sleep(5)
for i in range(10, 14):
    move_msg = controlTable()
    move_msg.dest = i
    move_msg.command_id = 5
    move_msg.value = 200

    pub.publish(move_msg)
    rospy.loginfo(move_msg)

for i in range(10, 14):
    move_msg = controlTable()
    move_msg.dest = i
    move_msg.command_id = 2
    move_msg.value = 500

    rospy.loginfo(move_msg)
    pub.publish(move_msg)


while not rospy.is_shutdown():
    move_to = int(input())
    if move_to == 1:
        movetoTrajectories(path)
    elif move_to == 2:
        movetoTrajectories(path2)
