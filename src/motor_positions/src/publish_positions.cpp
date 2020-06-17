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
#include "std_msgs/String.h"
#include <sstream>
#include <motor_positions/motorPosition.h>
#include <motor_positions/positionArray.h>
#include <motor_positions/controlTable.h>
#include <boost/thread/thread.hpp>

using std::cout;
//serial::Serial arduino;

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

void run(ros::NodeHandle node, serial::Serial arduino ){
   ros::Publisher publish = node.advertise<motor_positions::positionArray>("publish_positions", 1);
   while(1){
       
        if(arduino.available() >= 3){
            uint8_t check_buffer[3];
            arduino.read(check_buffer, 3);
            uint16_t check = INT_JOIN_BYTE(check_buffer[1], check_buffer[0]);
                //cout << "check:" << check << std::endl;
                if(int(check) != 60000){
                arduino.flushInput();
                cout << "flushed" << std::endl;
                
                } else {
                    motor_positions::motorPosition motor;
                    motor_positions::positionArray msg; 
                    int payload = int(check_buffer[2]);
                    uint8_t message_buffer[payload];
                    arduino.read(message_buffer, payload);

                    for(int i=0;i<payload -3;i+=3){
                        //cout << "id:" << int(message_buffer[i]) << std::endl;
                        int int_id = int(message_buffer[i]);
                        ROS_INFO_STREAM("id:" << int_id);
                        motor.motor_id = message_buffer[i];
                        uint16_t full_byte = INT_JOIN_BYTE(message_buffer[i + 2], message_buffer[i + 1]);
                        //cout << "position" << int(full_byte) << std::endl;
                        //cout << "---------" << std::endl;
                        int int_full_byte = int(full_byte);
                        ROS_INFO_STREAM("position" << int_full_byte);
                        motor.position = full_byte;
                        msg.positions.push_back(motor);
                    
                    publish.publish(msg);

                    }

                    if (message_buffer[payload - 1] != 244){
                    arduino.flushInput();
                    }
        }
                    
                }
          
    }
}

void controlCallback(motor_positions::controlTable msg, serial::Serial arduino){
    uint8_t control_buffer[8];

    control_buffer[0] = LOWER_BYTE(60000);
    control_buffer[1] = UPPER_BYTE(60000);
    control_buffer[2] = 5;
    control_buffer[3] = msg.motor_id;
    control_buffer[4] = msg.command_id;
    control_buffer[5] = LOWER_BYTE(msg.value);
    control_buffer[6] = UPPER_BYTE(msg.value);
    control_buffer[7] = 244;

    arduino.write(control_buffer, 8);

    
}

void subscribe(ros::NodeHandle node, serial::Serial arduino){
     ros::Subscriber sub = node.subscribe("dynamixel_control", 1000, boost::bind(controlCallback, _1, arduino));
     ros::spin();
}



int main(int argc, char**argv){
    ros::init(argc, argv, "publish_positions");
    ros::NodeHandle node;
    std::string vid_pid = "2341:0043"; 
    std::string port;

    std::vector<serial::PortInfo> devices_found = serial::list_ports();
    std::vector<serial::PortInfo>::iterator iter = devices_found.begin();

    while(iter != devices_found.end()){
        serial::PortInfo device = *iter++;
        if (device.hardware_id != "n/a"){
        std::string ids = device.hardware_id.substr(12, 10);
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


    //run(node);
    return 0;
}
