#include <ostream>
#include <string>
#include <iostream>
#include <cstdio>
#include "ros/init.h"
#include "ros/publisher.h"
//#include "serial/serial.h"
#include "serial/serial.h"
#include <math.h>
#include <std_msgs/String.h>
#include <unistd.h>
#include <chrono>
#include <queue>
#include <algorithm>

#include "ros/ros.h"
#include <sstream>
#include <motor_positions/motorPosition.h>
#include <motor_positions/positionArray.h>
#include <motor_positions/controlTable.h>

#define SendRate 20 //50 Hz return structure

#define UPPER_BYTE(b) (b >> 8) //defines byte structure 
#define LOWER_BYTE(b) (b & 0xff)
#define INT_JOIN_BYTE(u, l) (u << 8) | l
#define HeaderValue 60000 
using std::queue;
using std::vector;
using std::chrono::system_clock;
using std::chrono::milliseconds;

std::string port = "/dev/ttyACM0";
int baud = 115200;
serial::Serial teensy_serial(port, baud, serial::Timeout::simpleTimeout(1000));

queue<motor_positions::controlTable> controlMessages{};
vector<motor_positions::positionArray> recievedPositions{};

void writeSerial(){
    if(controlMessages.size() > 0){
        uint8_t bufferTransformSize = (controlMessages.size() * 4) + 4;

        ROS_INFO_STREAM("BufferInputSize:" << bufferTransformSize); 
        uint8_t control_buffer[bufferTransformSize];
        control_buffer[0] = LOWER_BYTE(uint16_t(HeaderValue));
        control_buffer[1] = UPPER_BYTE(uint16_t(HeaderValue));
        control_buffer[2] = controlMessages.size()*4+1;
        
        ROS_INFO_STREAM("Payload:" << int(control_buffer[2]));

        ROS_INFO_STREAM("Messages Needed to be sent:" << int(controlMessages.size())); 
        ROS_INFO_STREAM("Control Buffer is length of:" << sizeof (control_buffer));
        //std::cout << "Control Buffer[0] is length of:" << int(control_buffer[0]) << std::endl;
        //std::cout << "Control Buffer[1] is length of:" << int(control_buffer[1]) << std::endl;
        //std::cout << "Control Buffer[2] is length of:" << int(control_buffer[2]) << std::endl;

        /*for(int i = 0; i<55;i++){
            control_buffer[(i*4) + 3] = current_messages.motor_id;
            control_buffer[(i*4) + 4] = current_messages.command_id;
               
            control_buffer[(i*4) + 5] = LOWER_BYTE(current_messages.value);
            control_buffer[(i*4) + 6] = UPPER_BYTE(current_messages.value);
        }*/
        
        
        int max_size = std::min(40, int(controlMessages.size())) ;
        for(int i = 0; i<max_size;i++)
        {
            motor_positions::controlTable current_messages = controlMessages.front();
            control_buffer[(i*4) + 3] = current_messages.motor_id;
            control_buffer[(i*4) + 4] = current_messages.command_id;

            control_buffer[(i*4) + 5] = LOWER_BYTE(current_messages.value);
            control_buffer[(i*4) + 6] = UPPER_BYTE(current_messages.value);
            controlMessages.pop();
            i++;
        }

        control_buffer[bufferTransformSize-1] = 244;
        
        std::cout << "Final control buffer is length of:" << uint8_t(bufferTransformSize-1) << "   "<< (uint8_t)control_buffer[bufferTransformSize-1] << std::endl;


        teensy_serial.write(control_buffer, bufferTransformSize);
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
        controlMessages.push(msg);
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
    std::cout << teensy_serial.isOpen() << std::endl;
        
    ros::init(argc, argv, "publish_positions");
    ros::NodeHandle node;

    ros::Subscriber sub = node.subscribe("dynamixel_control", 100, controlCallback);

   ros::Publisher publisher = node.advertise<motor_positions::positionArray>("publisher_positions", 100);

    ros::Rate rate(40);

    while(1) {

//difference = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    //ROS_INFO_STREAM("difference" << difference);
    readSerial();
    publishPositions(publisher);
    writeSerial();
    //activation_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
rate.sleep();
ros::spinOnce();
    }

    return 0;
    
}
