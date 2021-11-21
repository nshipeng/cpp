/*
lock a mutex:
1. use std::lock_guard;
2. use lock(), unlock();
3. using unique lock //能够多次lock()与unlock(), 缺点是more heavy weigted lock_guard
*/

//deadlock 死锁
//进程申请的资源被其他等待的进程所占有,就会导致死锁
#include <iostream>
#include <thread>
#include<pthread.h>
#include <mutex>
#include <fstream>
using namespace std;

class LogFile{
    private:
        std::mutex mu;
        ofstream f;
        std::mutex mu_open;
        std::once_flag _flag;
    public:
        LogFile(){
        }
        void share_print_(string id,int value){
            // {
            //     std::unique_lock<mutex>locker2(mu_open);
            //     if(!f.is_open()){
            //         f.open("log.txt");
            //     }
            // }
            //使用once_flsg可以保证函数只被调用一次
            std::call_once(_flag,[&](){f.open("log.txt");}); //
            //std::unique_lock<mutex> locker(mu);
            std::unique_lock<mutex>locker (mu,std::defer_lock);//locker拥有mutex,但是mutex并未上锁
            //do something else
            locker.lock();
            f<<"From "<<id<< ": "<<value<<std::endl;
            locker.unlock();

            locker.lock();

            std::unique_lock<mutex> locker2 = std::move(locker);//转移mutex的所有权
        }
};

void fun1(LogFile& log){
    for(int i = 0;i<100;i++){
        log.share_print_("t1: ",i);
    }
}

//data race and mutex
//data race :不同的线程竞争共有的资源
int main(){
    LogFile log;
    std::thread t1(fun1,std::ref(log));
    for(int i=0;i<100;i++){
        log.share_print_("main: ",i);
    }
    t1.join();
    return 0;
}


