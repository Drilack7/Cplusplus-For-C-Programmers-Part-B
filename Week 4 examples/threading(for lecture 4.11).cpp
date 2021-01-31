//       flag -lpthread works
#include <iostream>
#include <string>
#include <thread>
using namespace std;

void message1(){ cout << "Write a Message!\n";}

int main()
{
        thread foo( []() {   //declare as a thread a lambda expression
                cout << "Hello World\n";
        } );
	thread thr1(message1);
	thr1.join();   //makes result defined
        foo.join();
}
