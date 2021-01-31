//#define NDEBUG
#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;


int main()
{
   uniform_int_distribution<int>  g(0, 1000000);
   default_random_engine e(time(nullptr));
   vector<int> data(1000);
   for (auto &element: data)
     element = g(e);
   sort(data.begin(), data.end());
   for (int i = 0; i < 999; i++)          //not great because left in
      assert( data[i] <= data[i + 1]);    //not < because equal elements
   cout << endl;

}
