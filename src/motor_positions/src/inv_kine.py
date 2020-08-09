#! /usr/bin/env python3
import rospy
import pdb
from math import atan2, sqrt, sin, cos, acos, pi

def leg_ikine(x_in, y_in, z_in, o_in, f, a):
    try:
        q = [0, 0, 0, 0]
        q[0] = atan2(y_in, x_in)
        r1 = sqrt(x_in**2 + y_in**2) - a[0]
        r2 = sqrt((z_in**2) + r1**2)
        p1 = atan2(z_in, r1)
        r3 = a[3] * sin(-1 * o_in)
        r4 = a[3] * cos(o_in)
        r5 = z_in + r3
        r6 = r1 - r4
        r7 = sqrt(r6**2 + r5**2)
        p2 = atan2(r5, r6)

        p3 = f * acos( (a[1]**2 + r7**2 - a[2]**2) / (2 * a[1] * r7))
        p4 = f * acos( (a[2]**2 + a[1]**2 - r7**2) / (2 * a[2] * a[1]))

        q[2] = pi - p4
        if f == -1:
            q[2] = q[2] - 2 * pi

        q[1] = p2 - p3

        q[3] = o_in - (q[1] + q[2])

        q[3] = 3.1455 - q[3]

        return(q)

    except ValueError:
        # print("Test")
        rospy.loginfo("Got a ValueError, probably a maths problem")


if __name__ == "__main__":
    a = [0.62, 0.86, 0.70, 0.61]
    test = leg_ikine(1.5, 0, 0, -pi/2, -1, a)
    pdb.set_trace()




