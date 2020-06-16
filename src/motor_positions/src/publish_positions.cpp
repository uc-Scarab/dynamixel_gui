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
using std::cout;


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

    //uint8_t alt_buffer[7];

    //alt_buffer[0] = LOWER_BYTE(60000);
    //alt_buffer[1] = UPPER_BYTE(60000);
    ////alt_buffer[2] = 4;
    //alt_buffer[3] = 2;
    //alt_buffer[4] = LOWER_BYTE(1000);
    //alt_buffer[5] = UPPER_BYTE(1000);
    //alt_buffer[6] = 244;

        //std::cout << "lower:" << int(alt_buffer[0]) << std::endl;
        //std::cout << "higher" << int(alt_buffer[1]) << std::endl;

        //arduino.write(alt_buffer, 7);

    //bool alt = true;
    while(1){

        //uint8_t out_message[7];
        //out_message[0] = LOWER_BYTE(60000);
        //out_message[1] = UPPER_BYTE(60000);
        //out_message[2] = 4;
        //out_message[3] = 5;

        //int position;
        //if(alt){
            //position = 1000;
        //} else {
            //position = 2000;
        //}

        //alt = !alt;

        //out_message[4] = LOWER_BYTE(position);
        //out_message[5] = UPPER_BYTE(position);
        //out_message[6] = 244;

        //arduino.write(out_message, 7);
        
        if(arduino.available() >= 3){
            uint8_t check_buffer[3];
            arduino.read(check_buffer, 3);
            uint16_t check = INT_JOIN_BYTE(check_buffer[1], check_buffer[0]);
                cout << "check:" << check << std::endl;
                if(int(check) != 60000){
                arduino.flushInput();
                cout << "flushed" << std::endl;
                
                } else {
                    int payload = int(check_buffer[2]);
                    uint8_t message_buffer[payload];
                    arduino.read(message_buffer, payload);

                    for(int i=0;i<payload -3;i+=3){
                        cout << "id:" << int(message_buffer[i]) << std::endl;
                        uint16_t full_byte = INT_JOIN_BYTE(message_buffer[i + 2], message_buffer[i + 1]);
                        cout << "position" << int(full_byte) << std::endl;
                        cout << "---------" << std::endl;
                    }

                    if (message_buffer[payload - 1] != 244){
                    arduino.flushInput();
                    }
        }
                    
                }
          
    }
}



int main(int argc, char**argv){
    run(argc, argv);
    return 0;
}
