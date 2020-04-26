import rospy
import serial
import platform
from dynamixel_gui.msg import DynamixelPosition

# note that the port on your system may be different, if so make the change here
if platform.system() == "Windows":
    arduino = serial.Serial("\\\\.\\COM8")
elif platform.system() == "Linux":
    arduino = serial.Serial("/dev/ttyUSB0")

arduino.baudrate = 115200


def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "stuff %s", data.motor_id)

    dyn_id = (int(data.motor_id)).to_bytes(1, byteorder="little")
    mode = (int(3)).to_bytes(1, byteorder="little")

    val = (int(data.position)).to_bytes(2, byteorder="little")

    ba_dyn_id = bytearray(dyn_id)
    ba_mode = bytearray(mode)
    ba_val = bytearray(val)

    ba_dyn_id.append(ba_mode[0])
    ba_dyn_id.append(ba_val[0])
    arduino.write(ba_dyn_id)


def listener():
    rospy.init_node("serial_coms", anonymous=True)

    rospy.Subscriber("dynamixel_gui/dynamixel_gui", DynamixelPosition, callback)
    rospy.spin()


if __name__ == "__main__":
    listener()
