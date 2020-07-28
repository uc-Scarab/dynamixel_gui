#include <ostream>
#include <string>
#include <iostream>
#include <cstdio>
#include "ros/init.h"
#include "ros/publisher.h"
#include "serial/serial.h"
#include <math.h>
#include <std_msgs/String.h>

#include <unistd.h>
#include <chrono>

#include "ros/ros.h"
#include <sstream>
#include <motor_positions/motorPosition.h>
#include <motor_positions/positionArray.h>
#include <motor_positions/controlTable.h>

#define SendRate 20 //50 Hz return structure

#define UPPER_BYTE(b) (b >> 8) //defines byte structure 
#define LOWER_BYTE(b) (b & 0xff)
#define INT_JOIN_BYTE(u, l) (u << 8) | l
using std::vector;
using std::chrono::system_clock;
using std::chrono::milliseconds;

std::string port = "/dev/ttyACM0";
int baud = 115200;
serial::Serial teensy_serial(port, baud, serial::Timeout::simpleTimeout(1000));

vector<motor_positions::controlTable> controlMessages{};
vector<motor_positions::positionArray> recievedPositions{};

void writeSerial(){
        if (controlMessages.size() != 0){ 
        uint8_t control_buffer[controlMessages.size()];
        control_buffer[0] = LOWER_BYTE(60000);
        control_buffer[1] = UPPER_BYTE(60000);
        control_buffer[2] = controlMessages.size()+1;
        
        for(int i = 0; i<controlMessages.size();i++){
            //ROS_INFO_STREAM(msg);
            control_buffer[i*4] = controlMessages[i].motor_id;
            control_buffer[i*4 + 1] = controlMessages[i+1].command_id;
               
            control_buffer[i*4 + 2] = LOWER_BYTE(controlMessages[i+2].value);
            control_buffer[i*4 + 3] = UPPER_BYTE(controlMessages[i+3].value);
        }


        control_buffer[controlMessages.size() + 4] = 244;


        teensy_serial.write(control_buffer, controlMessages.size() + 1);

        controlMessages.clear();
        }
}

        
void readSerial(){
        if(teensy_serial.available() >= 3){
            uint8_t check_buffer[3];
            teensy_serial.read(check_buffer, 3);
            uint16_t check = INT_JOIN_BYTE(check_buffer[1], check_buffer[0]);
                if(check != 60000){
                teensy_serial.flushInput();
                ROS_ERROR_STREAM("front: check:" << check);
                
                } else {
                    motor_positions::motorPosition motor;
                    motor_positions::positionArray msg; 
                    int payload = int(check_buffer[2]);
                    uint8_t message_buffer[payload];
                    teensy_serial.read(message_buffer, payload);
                    //TODO: add comment about for loop structure
                    for(int i=0;i<payload -3;i+=3){
                        //cout << "id:" << int(message_buffer[i]) << std::endl;
                        int int_id = int(message_buffer[i]);
                        ROS_INFO_STREAM("id:" << int_id);
                        motor.motor_id = message_buffer[i];
                        uint16_t full_byte = INT_JOIN_BYTE(message_buffer[i + 2], message_buffer[i + 1]);
                        //cout << "position" << int(full_byte) << std::endl;
                        //cout << "---------" << std::endl;
                        int int_full_byte = int(full_byte);
                        ROS_INFO_STREAM("position:" << int_full_byte);
                        motor.position = full_byte;
                        msg.positions.push_back(motor);
                    
                    //publisher.publish(msg);

                    }

                    recievedPositions.push_back(msg);

                    if (message_buffer[payload - 1] != 244){
                        ROS_ERROR_STREAM("back check" << message_buffer[payload - 1]);
                    teensy_serial.flushInput();
                    }
        }
                    
                }
          
    }



void controlCallback(motor_positions::controlTable msg) {
        controlMessages.push_back(msg);
}

void publishPositions(ros::Publisher pub){
    if (recievedPositions.size() > 0){
        for(motor_positions::positionArray array : recievedPositions){
            pub.publish(array);
        }
        recievedPositions.clear();
    }
}


int main(int argc, char**argv){
    ros::init(argc, argv, "publish_positions");
    ros::NodeHandle node;

    ros::Subscriber sub = node.subscribe("dynamixel_control", 100, controlCallback);

   ros::Publisher publisher = node.advertise<motor_positions::positionArray>("publisher_positions", 100);

    auto last_activation_write = std::chrono::high_resolution_clock::now();
;
auto last_activation_read = std::chrono::high_resolution_clock::now();

    auto time_now = std::chrono::high_resolution_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - last_activation_read).count(); 

    ros::Rate rate(1000);

        while(1) {

    time_now = std::chrono::high_resolution_clock::now();
    diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - last_activation_write).count(); 

    if(diff >= SendRate){
        //readSerial();
        writeSerial();
        publishPositions(publisher);
        last_activation_read = time_now;
    }
    ros::spinOnce();
    rate.sleep();
    }

    return 0;
    
}
