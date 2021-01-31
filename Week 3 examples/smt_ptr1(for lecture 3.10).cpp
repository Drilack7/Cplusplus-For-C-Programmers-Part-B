#include<memory>
#include<iostream>
using namespace std;

int main()
{

   cout  << "shared pointer  example"  << endl;
   shared_ptr <int> p1(new int (200));
   cout << *p1 << endl;

}

/* The above is new to C++11 where smart pointers are introduced.
*  shared_ptr<> is a class with pointer behavior as well as a "use"
*  semantics. The item pointed at maybe shared and its accessors
*  are tracked - until its "use == 0" leads to it being garbage collected.
*  This will allow us to simplify the 1998 Koenig program where we explicitly
*  have a "use" counter.
*
*  On a personal note, I and my PhD student Daniel Edelson invented smart pointers for this purpose
*  See, the Proxy pattern in "Design Patterns", Gamma, etal. p209.
*  D.R. Edelson and I. Pohl. "Smart Pointers: They're smart but they're not pointers."
*  In Proceedings of the 1991 Usenix C++ Conference.
*/



