#include <iostream>
#include <exception>
using namespace std;

class MyException : public exception
{
  public:
  const char * what () const throw ()
  {
    return "My Exception";
  }
};
 
int main()
{
  try
  {
    cout << "Do some Computing until something goes wrong.\n";
    throw MyException();
  }
  catch(MyException& e)
  {
    cout << "MyException caught" << endl;
    cout << e.what() << endl;
  }
}

