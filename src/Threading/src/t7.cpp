#include <future>
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>

using namespace std;

void fac(int n){
    int res = 1;
    for(int i = n; i>1; i--){
        res *= i;
    }
    cout<<"Res is : "<<res<<std::endl;
}

int fac_(int n){
    int res = 1;
    for(int i = n; i>1; i--){
        res *= i;
    }
    return res;
}

 int fac2(std::future<int>& f){
    int res = 1;
    int n = f.get();
    for(int i = n;i>1;i--){
        res*= i;
    }

    cout<<"Res is : "<<res<<std::endl;
    return res;
}

int main(){
    // std::thread t1(fac,4);
    // t1.join();

    //pass a value from child thread to main thread
    // int x;
    // std::future<int> fu = std::async(fac_,4);
    // x = fu.get();

    //pass a value from main thread to other thread
     int x;
     std::promise<int> p;                    // create promise
     std::future<int> f = p.get_future();    // engagement with future

     std::future<int> fu = std::async(std::launch::async, fac2, std::ref(f)); //// send future to new thread 
     //do something else .....
     std::this_thread::sleep_for(std::chrono::seconds(1));
     p.set_exception(std::make_exception_ptr(std::runtime_error("to err is human")));
    // p.set_value(4);                   // fulfill promise
    // x = fu.get();
    std:;cout<<"Get from child is :"<<x<<std::endl;
    return 0;

}