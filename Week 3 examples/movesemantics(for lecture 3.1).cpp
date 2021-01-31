#include <iostream>

using namespace std;

int main()
{
   int i {9};
   int* ptr_i ;
   int &&j = move(i);
   ptr_i = &j;
   cout << " Semantics of varoius declarations\n";
   cout  << "i  = "  << i << endl;
   cout  << "j  = "  << j << endl;
   cout  << "&i  = "  << &i << endl;
   cout  << "ptr_i  = "  << ptr_i << endl;
   ++i;
   cout  << "i  = "  << i << endl;
   cout  << "j  = "  << j << endl;

}
