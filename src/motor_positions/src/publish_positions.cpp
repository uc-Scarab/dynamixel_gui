#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "serial/serial.h"
#include "ros/ros.h"
#include <sstream>


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

    for(int i=0;i<10;i+=3){
        //ROS_INFO("test");
        int id = int(data_buffer[i]);
        ROS_INFO_STREAM("Motor ID:" << id);
       uint16_t full_byte = INT_JOIN_BYTE(int(data_buffer[i + 2]), int(data_buffer[i + 1])); 
       int position = int(full_byte);
        ROS_INFO_STREAM("Position:" << position); 
    }
    }
    }



int main(int argc, char**argv){
    run(argc, argv);
    return 0;
}
