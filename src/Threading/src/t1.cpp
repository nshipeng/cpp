#include <iostream>
#include <thread>
#include<pthread.h>

using namespace std;

void fun1(){
    std::cout<<"hello, world !"<<std::endl;
}
class Functor{
    public:

        void operator()(){
            for(int i=0;i>-100;i--){
                std::cout<<"from t1 "<<i<<std::endl;
            }
        }
};


//parameter to a thread is always pased by value
//if we want to passed by referece ,should use std::ref() 
class Fun{
    public:
        void operator()(std::string& s){
            std::cout<<"from t1: "<<s<<std::endl;
            s = "nwihuhrwbqrjhkwebr";
        }
};

int main(){

    std::cout<<std::thread::hardware_concurrency()<<std::endl;
    std::cout<<this_thread::get_id()<<std::endl;
    std::cout<<"......1"<<std::endl;
    // Functor fct;
    string s = "nieshipeng";
    std::thread t1((Fun()),std::ref(s));
    std::cout<<t1.get_id()<<std::endl;;
    // try{
    //     for(int i = 0;i<100;i++){
    //         std::cout<<"from main: "<<i<<std::endl;
    //     }       
    // }catch(...){
    //     t1.join();
    //     throw;
    // }
    std::thread t2 = std::move(t1);    //线程不能被拷贝构造,可以使用std::move()
    std::cout<<t2.get_id()<<std::endl;
    t2.join();    //main thread waits for t1 to finish
    //t1.detach();    //once detached ,detached forever
    std::cout<<s<<std::endl;
    
    std::cout<<".......2"<<std::endl;
    return 0;
}