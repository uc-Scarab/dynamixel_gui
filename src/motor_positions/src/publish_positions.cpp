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

#define UPPER_BYTE(b) (b >> 8) //defines byte structure 
#define LOWER_BYTE(b) (b & 0xff)
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

   //uint8_t first[6]; 
   //first[0] = LOWER_BYTE(60000);
   //first[1] = UPPER_BYTE(60000);
   //first[2] = 3;
   //first[3] = LOWER_BYTE(3000);
   //first[4] = UPPER_BYTE(3000);
   //first[5] = 244;

   //arduino.write(first, 6);

    while(1){
        uint8_t check_buffer[3];
        arduino.read(check_buffer, 3);
        uint16_t is_start = INT_JOIN_BYTE(check_buffer[0], check_buffer[1]);
        //std::cout << is_start << std::endl;
        //std::cout << int(check_buffer[2]) << std::endl;
        if(is_start == 60000){
            //std::cout << "is_start" << std::endl;
            int payload = check_buffer[2]; 
            uint8_t message_buffer[payload];
            arduino.read(message_buffer, payload);

        motor_positions::MotorPositions msg;
        int messages = payload - 1;
        int ids[messages/3];
        int positions[messages/3];

        for(int i=0;i<payload-3;i+=3){
            int id = int(message_buffer[i]);
            ROS_INFO_STREAM("Motor ID:" << id);
        uint16_t full_byte = INT_JOIN_BYTE(int(message_buffer[i + 1]), int(message_buffer[i + 2])); 
        int position = int(full_byte);
        positions[i] = position;
            ROS_INFO_STREAM("Position:" << position); 
        }

        //for(int i=0; i<payload; i++){
            //std::cout << i << " " <<int(message_buffer[i]) << std::endl;
        //}

        if (int(message_buffer[messages] != 244)){
            arduino.flushInput();
            std::cout << "flush" << std::endl;
            std::cout << int(message_buffer[messages]) << std::endl;
        }

        //for(int i=0; i<payload/3;i++){
            //msg.motor_id = ids[i];
            //msg.position = positions[i];
            //publish.publish(msg);
        //}
        //uint8_t out[payload + 3];
        //out[0] = LOWER_BYTE(65336);
        //out[1] = UPPER_BYTE(65336);
        //out[2] = payload;

        //for(int i=3; i<(payload - 3);i+=3){
            //out[i] = ids[i];
            //out[i + 1] = LOWER_BYTE(i + 1);
            //out[i + 2] = UPPER_BYTE(i + 2);
        //}

        //out[payload - 1] = 244;
        //arduino.write(out, payload + 3);
        


        }
    }
}



int main(int argc, char**argv){
    run(argc, argv);
    return 0;
}
