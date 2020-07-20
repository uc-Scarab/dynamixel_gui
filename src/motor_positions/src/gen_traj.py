#! /usr/bin/env python3
import rospy
from motor_positions.msg import controlTable
# from roboticstoolbox import mstraj
# import numpy as np
import pdb
# from std_msgs.msg import String

rospy.init_node('trajectories', anonymous=True)
pub = rospy.Publisher("dynamixel_control", controlTable, queue_size=10)
rate = rospy.Rate(10) # 10hz
test = controlTable()
while not rospy.is_shutdown():
    # rospy.loginfo("test")
    test.motor_id = 1
    test.command_id = 58
    test.value = 500
    pub.publish(test)
    # rate.sleep()

    # pub.publish("test")

# path = np.array([
        # [2173, 2526, 1412, 2502],
        # [2105,  1320, 1408, 2703],
        # [2070, 1539, 2394, 2194],
        # [2578, 2394, 2368, 2194]
        # ])


# out = mstraj(path, dt=0.1, tacc=5, tsegment=[2, 2, 2])
# # pdb.set_trace()

# move_msg = controlTable()
# while True:
    # for move in out.q:
        # # pdb.set_trace()
        # for count, via in enumerate(move):
            # move_msg.motor_id = count + 1
            # move_msg.command_id = 58
            # move_msg.value = via

            # # rospy.loginfo(move_msg)
            # pub.publish(move_msg)
        # rate.sleep()




