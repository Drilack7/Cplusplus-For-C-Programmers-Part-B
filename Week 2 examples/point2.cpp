#include <iostream>
#include <cmath> //sqrt()
using namespace std;

class duo{
   public:
     duo(double f = 0.0, double s = 0.0):first(f),second(s){}
     void set_first(double d){first = d;}
     void set_second(double d){second = d;}
     double get_first(){return first;}
     double get_second(){return second;}
   protected:  // intermediate data hiding –nb need for this example
     double first, second;
 };



 class point:public duo{
 public:
    point(double f = 0.0, double s = 0.0):duo(f, s){}  //initialize base object
    virtual double length(){ return sqrt(first* first + second* second);}
 };

 class point3d final:public point{//use final to discontinue inheritance
 public:
     point3d(double x = 0.0, double y = 0.0, double z = 0.0):point(x, y),z(z){}
     double length(){ return sqrt(first*first + second*second + z*z);}//virtual
     void set_z(double d){z = d;}
 private:
     double z;
 };

 int main()
 {
     point q, r(3.0, 4.0);
     q.set_first(3.0); q.set_second(4.0);
     cout << q.get_first() << ", "  << q.get_second() << endl;  //3, 4
     cout << q.length() << endl;                                //5
     point3d t;
     t.set_first(5.0); t.set_second(6.0); t.set_z(7.0);
     cout << t.length() << endl;                                //10.4881
     point3d w(6.0, 7.0, 8.0);
     point* ptr_p = &w; //base class pointer is polymorphic
     //w is point3d
     cout << "Call through polymorphic pointer\n";
     cout << ptr_p -> length() << endl; //compute point3d::length()
     ptr_p = &r;    //calls a pointer  2D
     cout << "Call through polymorphic pointer\n";
     cout << ptr_p -> length() << endl; //compute point::length()
 }
//Try changing duo protected to private.
//This is considered better data  hiding practice.
//In doing so you need to use accessor functios in length().
