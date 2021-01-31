#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;



int main()
{  
    const int size = 6;
    vector <int>  v(size);
    //classic for 
    for(int i = 0; i < size; ++i)
    {  
       v[i] = i;
       cout << v[i] << "\t";
    }
    cout << endl;
    //iterator logic + auto C++11
    for(auto p = v.begin(); p != v.end(); ++p)
       cout << *p << "\t";
    cout << endl;
    //for range 
    for(int element: v)
       cout << element  << "\t";
    cout << endl;
   
    //STL   C++11  lambda
    for_each(v.begin(), v.end(),
       [](int i){cout <<i << "\t";}
    );
    cout << endl;
    return 0;
}