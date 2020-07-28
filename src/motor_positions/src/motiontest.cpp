#include <iostream>
#include "ros/ros.h"
#include <motor_positions/controlTable.h>
#include <unistd.h>
#include <motor_positions/controlTableItems.h>
using std::cout;


int main(int argc, char**argv){

    ros::init(argc, argv, "dynamixel_control");

   ros::NodeHandle node;

   ros::Publisher publish = node.advertise<motor_positions::controlTable>("dynamixel_control", 60);

   motor_positions::controlTable msg;

   bool alt = true;
    while(ros::ok()){


        msg.value = 1300;
        msg.motor_id = 22;
        msg.command_id = 58;
        publish.publish(msg);
        usleep(200000);
    }
    
     return 0; 
    } 

    

