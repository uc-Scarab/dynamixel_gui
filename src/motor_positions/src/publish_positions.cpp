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

    while(iter != devices_found.end()){
        serial::PortInfo device = *iter++;
        //std::cout << "hids" << device.hardware_id << std::endl;
        if (device.hardware_id != "n/a"){
        std::string ids = device.hardware_id.substr(12, 10);
        //std::cout << "hardware:" << device.hardware_id << std::endl;
        //std::cout << "description:" << device.description << std::endl;
        //std::cout << "vid_pid:" << vid_pid << std::endl;
        //std::cout << "ids:" << ids << std::endl;
        ////std::cout << "port:" << device.port << std::endl;
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
        uint8_t check_buffer[3];
        size_t result = arduino.read(check_buffer, 3);
        int is_start = int(INT_JOIN_BYTE(check_buffer[1], check_buffer[0]));
        if(is_start == 65336){
            int payload = check_buffer[2]; 
            uint8_t message_buffer[payload];
            arduino.read(message_buffer, payload);

        motor_positions::MotorPositions msg;
        int ids[payload/3];
        int positions[payload/3];

        for(int i=0;i<payload-3;i+=3){
            //ROS_INFO("test");
            int id = int(message_buffer[i]);
            ROS_INFO_STREAM("Motor ID:" << id);
        uint16_t full_byte = INT_JOIN_BYTE(int(message_buffer[i + 2]), int(message_buffer[i + 1])); 
        int position = int(full_byte);
        positions[i] = position;
            ROS_INFO_STREAM("Position:" << position); 
        }

        if (int(message_buffer[payload - 1] != 244)){
            arduino.flushInput();
        }

        for(int i=0; i<payload/3;i++){
            msg.motor_id = ids[i];
            msg.position = positions[i];
            publish.publish(msg);
        }

        }
    }
}



int main(int argc, char**argv){
    run(argc, argv);
    return 0;
}
