#include <boost/thread/thread.hpp>
//#include <thread>
#include <iostream>
     

//void test(){
    //while(1){
    //std::cout << "test" << std::endl;
    //}
//}

//int main(int argc, char**argv){
    ////boost::thread t{test};
    ////t.detach();
    //std::thread test;

    //test.detach();
    ////while(1){
        ////std::cout << "main" << std::endl;
    ////}
    //return 0;
//}
    
    // CPP program to demonstrate multithreading 
// using three different callables. 
#include <iostream> 
//#include <thread> 
#include <pthread.h>
#include <unistd.h>
using namespace std; 

int miliseconds = 1000;

void echo1() {
    while(1){
    std::cout << "1" << std::endl;
    usleep(1000 * miliseconds);
    }
}

void echo2(){
    while(1){
        std::cout << "2" << std::endl;
        usleep(1000 * miliseconds);
    }
}


// A callable object 
int main() 
{ 
    boost::thread thread1(echo1);
    boost::thread thread2(echo2);

    thread1.join();
       thread2.join(); 
       return 0;
} 

