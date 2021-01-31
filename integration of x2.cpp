#include <iostream>
#include <vector>
#include <algorithm> //generate
#include <numeric> //accumulate
using namespace std;

class gen
{
public:
    gen(double x_zero, double increment):x(x_zero),incr(increment){}
    double operator()(){x += incr; return x*x;}
private:
    double x, incr;
};

double integrate(gen g, int n)
{
    vector<double> fx(n);
    generate(fx.begin(), fx.end(), g);
    return (accumulate(fx.begin(), fx.end(), 0.0)/n);
}

int main()
{
    const int n=10000;

    gen g(0.0, 1.0/n);
    cout << "integration program x**2" << endl;
    cout << integrate(g,n) << endl;
}
