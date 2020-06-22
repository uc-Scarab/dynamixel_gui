#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <motor_positions/controlTable.h>


    void controlCallback(motor_positions::controlTable msg){
     ROS_INFO("working");   
    //uint8_t control_buffer[8];

    //control_buffer[0] = LOWER_BYTE(60000); control_buffer[1] = UPPER_BYTE(60000);
    //control_buffer[2] = 5;
    //control_buffer[3] = msg.motor_id;
    //control_buffer[4] = msg.command_id;
    //control_buffer[5] = LOWER_BYTE(msg.value);
    //control_buffer[6] = UPPER_BYTE(msg.value);
    //control_buffer[7] = 244;

    //this->arduino.write(control_buffer, 8);

    
}

     



int main(int argc, char**argv){
    ros::init(argc, argv, "publish_positions");
    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe("dynamixel_control", 1000, controlCallback);
     ros::spin();
     return 0;
}
    
    
