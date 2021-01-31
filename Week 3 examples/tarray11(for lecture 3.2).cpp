#include <iostream>
using namespace std;

template <class T, int n>
class my_container {
public:
   my_container(){ a = new T[n];}
   explicit my_container(T *b):my_container()
   {
      for(int i = 0; i <n ; ++i)
          a[i] = b[i];
   }
   my_container(const my_container &b):my_container()
   {
      for(int i = 0; i <n ; ++i)
          a[i] = b.a[i];
   }
   my_container(my_container &&b)noexcept
   {
      a = b.a;
      b.a = nullptr;
   }
   my_container& operator=(const my_container& b){
      for(int i = 0; i <n ; ++i)
          a[i] = b.a[i];
	  return *this;
   }
   my_container& operator=(my_container&& b)noexcept
   {
      a = b.a;
      b.a = nullptr;
      return *this;
   }
   void fill(T x)
   {
      for(int i = 0; i <n ; ++i)
          a[i] = x;
  }
  void print()
  {
      if (a == nullptr){ cout << "empty" << endl; return;}
      for(int i = 0; i <n ; ++i)
          cout << a[i] << ",";
          cout << endl;
  }
  void swap(my_container &b)
  {
      my_container temp = move(b);
      b = move(*this);
      *this  = move(temp);
  }
  T& operator[](int index) // [],=,(), -> must be members
  { return(a[index]);}

private:
   T*  a;
};


int main ()
{
  double data [10]{1,2,3,4,5,6,7,8,9,10};
  my_container<double,5>  x;
  my_container<double,5>  y(data);
  x.fill(2.0);
  x.print();
  y.print();

  y.swap(x);  //move based swap
  x.print();
  y.print();
  x =  move(y);
  x.print();
  y.print();
  cout<< " one element in x is "  << x[3] << endl;
}
