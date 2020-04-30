#!/usr/bin/python
import rospy
import serial
from dynamixel_gui.msg import DynamixelPosition
# import pdb

arduino = serial.Serial("/dev/ttyUSB1")
arduino.baudrate = 115200

while True:
    # motor_2 = arduino.read(2)
    # motor_3 = arduino.read(2)
    # motor_4 = arduino.read(2)
    # motor_5 = arduino.read(2)

    raw = str(arduino.readline())

    motor_positions = list(map(int, raw[2:-5].split(",")))
    # pdb.set_trace()

    print(motor_positions)

    # pdb.set_trace()
