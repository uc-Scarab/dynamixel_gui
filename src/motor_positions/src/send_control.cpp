#include <iostream>
#include "ros/ros.h"
#include <motor_positions/controlTable.h>
#include <unistd.h>
using std::cout;

int main(int argc, char**argv){

    ros::init(argc, argv, "dynamixel_control");

   ros::NodeHandle node;

   ros::Publisher publish = node.advertise<motor_positions::controlTable>("dynamixel_control", 1);

   //bool alt = true;
   //
    while(ros::ok()){
    

     
    motor_positions::controlTable msg;

    //for(int i=5 ; i<6; i++ ){ 
        msg.motor_id = 5;
        msg.command_id = 30;
        msg.value = 2048;
        publish.publish(msg);
        ROS_INFO_STREAM(msg);


    //}

        usleep(2000000);
        //alt = !alt;

        }
 
    return 0;
}
