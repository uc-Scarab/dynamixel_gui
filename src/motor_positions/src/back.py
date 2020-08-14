#!/usr/bin/env python3
# license removed for brevity
import rospy
# from std_msgs.msg import String
from motor_positions.msg import controlTable

def talker():
    test = controlTable()
    test.dest = 12
    test.command_id = 2
    test.value = 500
    pub = rospy.Publisher('dynamixel_control', controlTable, queue_size=100)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        rospy.loginfo(test)
        pub.publish(test)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass

