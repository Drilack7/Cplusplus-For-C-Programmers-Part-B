//4.6  assert example

#include <iostream>
#include <cassert>
using namespace std;

inline void print(int *myInt)
{
   assert(myInt != nullptr);
   cout << *myInt << endl;
}

int main()
{
   int i = 5;
   int *p = &i;
   int *q = nullptr;
   print(&i);
   print(p);
   print(q);
}
