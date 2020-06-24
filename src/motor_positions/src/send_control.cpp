#include <iostream>
#include "ros/ros.h"
#include <motor_positions/controlTable.h>
#include <unistd.h>
using std::cout;

int main(int argc, char**argv){

    ros::init(argc, argv, "dynamixel_control");

   ros::NodeHandle node;

   ros::Publisher publish = node.advertise<motor_positions::controlTable>("dynamixel_control", 1);

   bool alt = true;
    while(1){
    

     
    motor_positions::controlTable msg;

    msg.motor_id = 5;
    msg.command_id = 30;
    if(alt){
    msg.value = 500;
    } else {
        msg.value = 3500;
    }

    alt = !alt;

    publish.publish(msg);
    ROS_INFO_STREAM(msg);
    usleep(2000000);
    }
 
    return 0;
}
