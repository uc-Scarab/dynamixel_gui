#include <iostream>
#include "ros/ros.h"
#include <motor_positions/controlTable.h>
#include <unistd.h>
#include <motor_positions/controlTableItems.h>
using std::cout;


int main(int argc, char**argv){

    ros::init(argc, argv, "dynamixel_control");

   ros::NodeHandle node;

   ros::Publisher publish = node.advertise<motor_positions::controlTable>("dynamixel_control", 1);

   bool alt = true;
   //
    while(ros::ok()){
    

     
    motor_positions::controlTable msg;

    usleep(2000000);

    for(int i=1 ; i<5; i++ ){ 
       if(alt){
            msg.value = 2048;
        } else {
            msg.value = 2048;
        }
        msg.motor_id = i;
        msg.command_id = GOAL_POSITION;
        publish.publish(msg);
        ROS_INFO_STREAM(msg);

        usleep(2000000);

        alt = !alt;
    }


        }
    
     return 0; 
    } 

    

