#include <iostream>
#include <thread>
#include<pthread.h>
#include <deque>
#include <mutex>
#include <condition_variable>
using namespace std;

//with condition variable, we can make the thread running in the fixed order
std::deque<int> q;
std::mutex mtx;
std::condition_variable cod;
void fun1(){
    int count = 10;
    while(count > 0){
        std::unique_lock<mutex>locker (mtx);
        q.push_back(count);
        locker.unlock();
        cod.notify_one(); //Notify one watting thread, if there is one.

        std::this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

void fun2(){

    int data = 0;
    while(data != 1){
        std::unique_lock<mutex> locker2(mtx);
        cod.wait(locker2,[](){return !q.empty();}); //wait until q is not empty
        data = q.back();
        q.pop_back();
        locker2.unlock();
        std::cout<<"t2 get a value from t1 : "<<data<<std::endl;
        // if(!q.empty()){
        //     data = q.back();
        //     q.pop_back();
        //     locker2.unlock();
        //     std::cout<<"t2 get a value from t1 : "<<data<<std::endl;
        // }else{
        //     locker2.unlock();//一直查询无效率,可以让线程休眠,问题即为:应该让线程休眠多久? 由此引入condition_variable
        //     std::this_thread::sleep_for(chrono::seconds(10));
        // }
    }

}

int main(){
    std::thread t1(fun1);
    std::thread t2(fun2);
    t1.join();
    t2.join();
    return 0;
}


