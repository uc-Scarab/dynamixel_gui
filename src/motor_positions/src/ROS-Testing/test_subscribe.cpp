//#include <boost/thread/thread.hpp>
//#include <thread>
//#include <iostream>
//#include <motor_positions/trajectory.h>
#include "std_msgs/String.h"
#include "ros/ros.h"
#include <iostream> 
//#include <thread> 
//#include <pthread.h>
//#include <unistd.h>
using std::cout; 
void controlCallback(std_msgs::String msg){
    ROS_INFO_STREAM(msg);
}



int main(int argc, char** argv) 
{ 
    ros::init(argc, argv, "publish_positions");
    ros::NodeHandle node;
 
    ros::Subscriber sub = node.subscribe("test", 1000, controlCallback);
    ros::spin();
    return 0;
}
 

