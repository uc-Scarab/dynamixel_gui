#! /usr/bin/env python3
import rospy
from math import atan2, sqrt, sin, cos, acos, pi

# rospy.init_node('trajectories', anonymous=True)
# pub = rospy.Publisher("dynamixel_control", controlTable, queue_size=10)
# rate = rospy.Rate(10) # 10hz

def leg_ikine(x_in, y_in, z_in, o_in, f, a):
    q = []
    q[0] = atan2(y_in, x_in)
    r1 = sqrt(x_in^2 + y_in^2) - a[0]
    r2 = sqrt(z_in^2 + r1^2)
    p1 = atan2(z_in, r1)
    r3 = a[3] * sin(-1 * o_in)
    r4 = a[3] * cos(o_in)
    r5 = z_in + r3
    r6 = r1 + r4
    r7 = sqrt(r6^2 + r5^2)
    p2 = atan2(r5, r6)

    p3 = f * acos( a[1]^2 + r7^2 -a[2]^2) / (2 * a[1] * r7)
    p4 = f * acos( a[2]^2 + a[1]^2 - r7^2) / (2 * a[2] * a[1])

    q[2] = pi - p4
    q[1] = p2 - p3

    q[3] = o_in - (q[1] + q[2])






