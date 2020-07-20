import rospy
from std_msgs.msg import String

rospy.init_node('test', anonymous=True)
pub = rospy.Publisher("test", String, queue_size=10)

while True:
    pub.publish("test")
