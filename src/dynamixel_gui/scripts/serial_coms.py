import rospy
from dynamixel_gui.msg import DynamixelPosition


def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "stuff %s", data.motor_id)


def listener():
    rospy.init_node("serial_coms", anonymous=True)

    rospy.Subscriber("dynamixel_gui/dynamixel_gui", DynamixelPosition, callback)
    rospy.spin()


if __name__ == "__main__":
    listener()
