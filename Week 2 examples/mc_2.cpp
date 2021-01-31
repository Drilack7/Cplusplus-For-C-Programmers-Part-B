#include<iostream>
#include<random>
#include<vector>
#include<tuple>  //C++11
#include<algorithm>
#include<ctime>   //use time(nullptr) for seed
#include<cmath>   //use sqrt

using namespace std;



typedef tuple<double, double> point;
ostream& operator<<(ostream& out, const point&  pt)
{
   out  << "( " << get<0>(pt) << ", ";
   out << get<1>(pt) << ") ";
   return out;
}

point random_point()
{

   uniform_real_distribution<double> u(0, 1);
   point temp;
   get<0>(temp) = u(e);
   get<1>(temp) = u(e);
   return temp;
}

double mc_count(double f(double), vector<point>::iterator first , vector <point>::iterator last)
{
   int trials = 0; int below = 0;
   for(first; first != last; ++first){
      ++trials;
      if (f(get<0>(*first)) > get<1>(*first))
        ++below;
   }
   return( 1.0* below/trials);
}

int main()
{
   default_random_engine  e(time(nullptr));  //seed in constructor
   int data_size;
   cout << " How Many Points? " << endl;
   cin >> data_size;
   vector<point> data(data_size);
   for(auto& element: data)
       element = random_point();


    cout << " PI by MC integration is " <<
       4.0 * mc_count([](double x){ return (sqrt( 1 - x * x));}, data.begin(), data.end());
    cout <<endl;

}
