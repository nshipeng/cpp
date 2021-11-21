/*
 * @Description: https://www.runoob.com/w3cnote/cpp-func-pointer.html
 * @Version: 2.0
 * @Autor: 
 * @Date: 2021-11-16 11:38:21
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-11-16 14:08:11
 */
#include <iostream>

using namespace std;

int test(int a){
    std::cout<<a<<std::endl;
    return a;

}

class A
{
private:
    int a;
public:
    A(int aa):a(aa){};
    A() = default;
    ~A(){};
    void setA(int aa = 1){
        a = aa;
    }
    virtual void print(){
        std::cout<<"A "<<a<<std::endl;
    }

    virtual void printa(){
        std::cout<<"A1 "<<a<<std::endl;
    }

    
    //virtual void pure_virtual() = 0;
};

class B :public A{
    public:
        B():A(), b(0){}
        B(int aa,int bb):A(aa),b(bb){}

        virtual void print(){
            A::print();
            std::cout<<"B : "<<b<<std::endl;
        }
        ~B(){}

        virtual void printa(){
            A::printa();
            std::cout<<"B : "<<b<<std::endl;
        }

        // virtual void pure_virtual() override{
        //     std::cout<<" pure test "<<std::endl;
        // }


    private:
        int b;

};


int main(){

    int(*p)(int a);
    p = test;
    std::cout<<p(2)<<std::endl;
   
    A a;
    B b;
   
   void (A::*ptr)(int a) = &A::setA;
   A* pa = &a;

  printf("A::set() : %p\n", &A::setA);
  printf("A::print() : %p\n",&A::print);
  printf("A::printa() : %p\n",&A::printa);


   a.print();
   a.setA(10);
   a.print();

   (pa->*ptr)(1000);
   a.print();

   (a.*ptr)(10000);
   a.print();


    return 0;
}