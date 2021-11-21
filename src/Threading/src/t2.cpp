#include <iostream>
#include <thread>
#include<pthread.h>
#include <mutex>
#include <fstream>
using namespace std;

std::mutex mu;
void shared_print(std::string msg, int id){
    std::lock_guard<mutex> guard(mu);
    //mu.lock();
    std::cout<<msg<<id<<std::endl;
    //mu.unlock();
}

class LogFile{
    private:
        std::mutex mu;
        ofstream f;
    public:
        LogFile(){
            f.open("log.txt");
        }
        void share_print_(string id,int value){
            std::lock_guard<std::mutex>locker(mu);
            f<<"From "<<id<< ": "<<value<<std::endl;
        }
};

void fun1(){    
    for(int i = 0;i>-100;i--){
        shared_print("From t1: ",i);
    }
}


//data race and mutex
//data race :不同的线程竞争共有的资源
int main(){
    std::thread t1(fun1);
    for(int i=0;i<100;i++){
        shared_print("From Main: ",i);
    }
    t1.join();
    return 0;
}