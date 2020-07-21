#! /usr/bin/env python3
import rospy
from motor_positions.msg import controlTable
from roboticstoolbox import mstraj
import numpy as np
import pdb
# from std_msgs.msg import String

rospy.init_node('trajectories', anonymous=True)
pub = rospy.Publisher("dynamixel_control", controlTable, queue_size=10)
rate = rospy.Rate(10) # 10hz
test = controlTable()

path = np.array([
        [0, -0.4249, -0.5008, -0.7019],
        [0,  0.4857, -0.1366, -0.4553]
        ])


out = mstraj(path, dt=0.1, tacc=5, tsegment=[2])

move_msg = controlTable()
while True:
    for move in out.q:
        # pdb.set_trace()
        for count, via in enumerate(move):
            move_msg.motor_id = count + 1
            move_msg.command_id = 58
            move_msg.value = via

            rospy.loginfo(move_msg)
            pub.publish(move_msg)
        rate.sleep()




