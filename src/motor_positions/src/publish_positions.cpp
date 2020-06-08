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
    std::string vid_pid = "2341:0043"; 
    std::string port;

    std::vector<serial::PortInfo> devices_found = serial::list_ports();
    std::vector<serial::PortInfo>::iterator iter = devices_found.begin();

    while( iter != devices_found.end()){
        serial::PortInfo device = *iter++;
        //std::cout << "hids" << device.hardware_id << std::endl;
        if (device.hardware_id != "n/a"){
        std::string ids = device.hardware_id.substr(12, 10);
        //std::cout << "hardware:" << device.hardware_id << std::endl;
        std::cout << "vid_pid:" << vid_pid << std::endl;
        std::cout << "ids:" << ids << std::endl;
        //std::cout << "port:" << device.port << std::endl;
        //std::cout << "length" << device.hardware_id.length() << std::endl;
        //std::cout << "substring length" << ids.length() << std::endl;
        if (ids.compare(vid_pid)){
            port = device.port;
        }
        }

    }


    std::cout << "Port:" << port << std::endl;
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
