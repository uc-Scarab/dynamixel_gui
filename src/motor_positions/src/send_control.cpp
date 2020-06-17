#include <iostream>
#include "ros/ros.h"
#include <motor_positions/controlTable.h>

using std::cout;


void run(ros::NodeHandle node ){
   ros::Publisher publish = node.advertise<motor_positions::controlTable>("dynamixel_control", 1);
    

     
    motor_positions::controlTable msg;

    msg.motor_id = 5;
    msg.command_id = 24;
    msg.value = 1;

    publish.publish(msg);

       }
                    
          


int main(int argc, char**argv){
    ros::init(argc, argv, "dynamixel_control");
    ros::NodeHandle node;
 
    run(node);
    return 0;
}
