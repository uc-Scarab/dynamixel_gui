#include <string>
#include <iostream>
#include <cstdio>
#include "serial/serial.h"
// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "ros/ros.h"
#include <sstream>
#include <motor_positions/MotorPositions.h>


void my_sleep(unsigned long milliseconds){
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds*1000);
    #endif
}

#define INT_JOIN_BYTE(u, l) (u << 8) | l

int run(int argc, char **argv){
    ros::init(argc, argv, "publish_positions");
    ros::NodeHandle node;
    ros::Publisher publish = node.advertise<motor_positions::MotorPositions>("publish_positions", 1);
    std::string port = "/dev/ttyACM0";
    unsigned long baud = 115200;

    serial::Serial arduino(port, baud, serial::Timeout::simpleTimeout(1000));
    if(arduino.isOpen())
        std::cout << "Yes." << std::endl;
    else
        std::cout << " No." << std::endl;


    while(1){
            uint8_t data_buffer[12];
        size_t result = arduino.read(data_buffer, 12);
        std::cout << int(data_buffer[0]) << std::endl;

    motor_positions::MotorPositions msg;
    int ids[4];
    int positions[4];

    for(int i=0;i<10;i+=3){
        //ROS_INFO("test");
        int id = int(data_buffer[i]);
        ROS_INFO_STREAM("Motor ID:" << id);
       uint16_t full_byte = INT_JOIN_BYTE(int(data_buffer[i + 2]), int(data_buffer[i + 1])); 
       int position = int(full_byte);
       positions[i] = position;
        ROS_INFO_STREAM("Position:" << position); 
    }

    msg.position_2 = positions[0];
    msg.position_3 = positions[1];    
    msg.position_4 = positions[2];
    msg.position_5 = positions[3];

    publish.publish(msg);    
    }
    }



int main(int argc, char**argv){
    run(argc, argv);
    return 0;
}
