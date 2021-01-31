//Simple STL vector program with 2 options
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int>v(100); //allocate space

    for (int i=0; i<100; ++i) //C idiom
        v[i] = i; //index through like an array

    //First option
    for (vector<int>::iterator p = v.begin(); p != v.end(); ++p) //C++ idiom
        cout << *p << "\t";
    cout << endl << endl;

    //Second option -> range-based for loop
    for (auto i:v)  //C++11 idiom
        cout << i << "\t";
    cout << endl;
}
