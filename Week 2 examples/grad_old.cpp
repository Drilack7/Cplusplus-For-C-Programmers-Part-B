//Code as largely seen in C++ For C Programmers Part B
//Before changes are made to use <string>
//The current C++11 practice is to use <string>
//Using char* may lead to compiler warnings about
//this practice being deprecated.

#include <iostream>
#include <cstring>  //uses c style char*

using namespace std;


class student {
public:
   enum year {fresh, soph, junior, senior, grad};
   student(char* nm, int id, double g, year x);
   void  print();
protected:
   int       student_id;
   double    gpa;
   year      y;
   char      name[30];
};

class grad_student: public student {
public:
   enum support {ta, ra, fellowship, other};
   grad_student
      (char* nm, int id, double g, year x, support t, char* d, char* th);
   void print();
protected:
   support      s;
   char         dept[10];
   char         thesis[80];
};
student::student(char* nm, int id, double g, year x)
		:student_id(id), gpa(g), y(x)
{
   strcpy(name, nm);
}



grad_student::grad_student(
   char* nm, int id, double g, year x,
   support t, char* d, char* th)
   :student(nm, id, g, x), s(t)
{
   strcpy(dept, d);
   strcpy(thesis, th);
}



void student::print()
{
   cout << "\n" << name << " , " << student_id << " , "
	<< y << " , " << gpa << endl;
}

void grad_student::print()
{
   student::print();    //base class information is printed
   cout << dept << " , " << s << "\n" << thesis << endl;
}
//Test pointer conversion rules.

main()
{
   student        s("Mae Pohl", 100, 3.425, student::fresh), *ps = &s;
   grad_student   gs("Morris Pohl", 200, 3.2564,
		     student::grad, grad_student::ta, "Pharmacy",
		    "Retail Pharmacies"), *pgs;

   ps -> print();     //student::print
   ps = pgs = &gs;
   ps -> print();     //student::print
   pgs -> print();    //grad_student::print
}

