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
        std::mutex mu2;
        ofstream f;
    public:
        LogFile(){
            f.open("log.txt");
        }
        void share_print_(string id,int value){
            std::lock(mu,mu2);
            std::lock_guard<std::mutex>locker(mu,std::adopt_lock);
            std::lock_guard<std::mutex>locker2(mu2,std::adopt_lock);
            std::cout<<"From "<<id<< ": "<<value<<std::endl;
        }
        void share_print_2(string id,int value){
            std::lock(mu,mu2);
            std::lock_guard<std::mutex>locker(mu,std::adopt_lock);
            std::lock_guard<std::mutex>locker2(mu2,std::adopt_lock);
            std::cout<<"From "<<id<< ": "<<value<<std::endl;
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
        log.share_print_2("main: ",i);
    }
    t1.join();
    return 0;
}

/*
1.prefer locking single mutex;
        {
            std::lock_guard<mutex>locker(mu);
            ///.......
        }
        {
            std::lock_guard<mutex>locker2(mu2);
            /.....
        }
2.Avoid locking a mutex and then calling a user provided function.
3.use std::lock() to lock more than one mutex.
4 Lock the mutex in same order.

*/