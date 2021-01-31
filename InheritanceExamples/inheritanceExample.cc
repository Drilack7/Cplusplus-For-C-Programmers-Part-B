#include <iostream>
#include <cmath>
using namespace std;

class duo
{
public:
    duo():first(0.0),second(0.0){}
    void set_first(double d){first = d;}
    void set_second(double d){second = d;}
    double get_first(){return first;}
    double get_second(){return second;}
protected:
    double first, second;
};

class point:public duo
{
public:
    double length(){return sqrt(first*first + second*second);}
};

int main()
{
    point q;
    q.set_first(3.0);
    q.set_second(4.0);

    cout << q.get_first() << "," << q.get_second() << endl;
    cout << q.length() << endl;

    return 0;
}
