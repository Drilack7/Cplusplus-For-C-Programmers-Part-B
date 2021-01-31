//C++ For C Programmers Part B  2.13
//Ira Pohl   April 2016
//overriding behavior

#include <iostream>

 class B {
 public:
    int i;
    virtual void print_i() const
      { std::cout << i << " inside B" << std::endl; }
 };

 class D: public B {
 public:
    void print_i() const 
       { std::cout << i << " inside D" << std::endl; }
 };
 
 int main()
 {
     B   b;
     B*  pb = &b;      //point at a B object
     D   f;
     f.i = 1 + (b.i = 1);
     pb -> print_i();  //call B::print_i()
     pb = &f;          //point at a D object
     pb -> print_i();  //call D::print_i()
 }

