#!/usr/bin/python3
import rospy
import serial
from dynamixel_gui.msg import DynamixelPosition
import pdb


def publisher():
    arduino = serial.Serial("/dev/ttyUSB1")
    arduino.baudrate = 115200
    pub = rospy.Publisher("motor_positions", DynamixelPosition, queue_size=1)
    rospy.init_node("current_positions", anonymous=True)
    rate = rospy.Rate(0.1)

    while not rospy.is_shutdown():
        # motor_2 = arduino.read(2)
        # motor_3 = arduino.read(2)
        # motor_4 = arduino.read(2)
        # motor_5 = arduino.read(2)

        raw = str(arduino.readline())
        motor_positions = list(map(int, raw[2:-5].split(",")))

        positions = DynamixelPosition()

        positions.motor_2 = motor_positions[0]
        positions.motor_3 = motor_positions[1]
        positions.motor_4 = motor_positions[2]
        positions.motor_5 = motor_positions[3]

        pdb.set_trace()
        rospy.loginfo(positions)
        pub.publish(positions)
        rate.sleep()


if __name__ == "__main__":
    try:
        publisher()
    except rospy.ROSInterruptException:
        pass
