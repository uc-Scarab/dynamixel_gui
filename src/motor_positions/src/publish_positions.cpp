#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "serial/serial.h"



//void my_sleep(unsigned long milliseconds){
    //#ifdef _WIN32
        //Sleep(milliseconds);
    //#else
        //usleep(milliseconds*1000);
    //#endif
//}

#define INT_JOIN_BYTE(u, l) (u << 8) | l

int run(){
    std::string port = "/dev/ttyUSB1";
    unsigned long baud = 115200;

    //vector<serial::PortInfo> devices_found = serial::list_ports();
    //std::cout << devices_found;
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
        std::cout << "Motor ID:\n" << int(data_buffer[i]) << std::endl; 
       uint16_t position = INT_JOIN_BYTE(int(data_buffer[i + 2]), int(data_buffer[i + 1])); 
        std::cout << "Position:\n" << int(position) << std::endl; 
    }
    }
    }



int main(){
    run();
    return 0;
}
