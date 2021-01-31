#include <map>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    map<unsigned long, string> worker;
    unordered_map<unsigned long, unsigned> payroll;
    unsigned total_pay=0;
    worker[99567800] = "Harold Fish";
    payroll[99567800] = 67300;
    worker[8567800] = "Phillip Fish";
    payroll[8567800] = 87300;

    for (auto p=worker.begin(); p!=worker.end(); ++p)
        cout << "name " << (*p).second << "\t id no. " << (*p).first << endl;
    for (auto p=payroll.begin(); p!=payroll.end(); ++p)
        total_pay += (*p).second;
    cout << "payroll totals $" << total_pay << endl;
}
