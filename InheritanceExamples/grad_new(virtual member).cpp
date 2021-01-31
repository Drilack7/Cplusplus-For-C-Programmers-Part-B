

//C++ For C Programmers Part B
//Ira Pohl April 2016
//add ostream
//hierarchy person
//redo print for enum class
#include <iostream>
#include <string>

using namespace std;


enum class year {fresh, soph, junior, senior, grad};
class student {
public:
   student(string nm, int id, double g, year x); 
   virtual void  print()const;
protected:
   int       student_id;
   double    gpa;
   year      y;
   string    name;
};

ostream& operator<<(ostream& out, const year & yr)
{
   if (yr == year::fresh) out << " Fresh ";
   else if (yr == year::soph) out << " Soph ";
   else if (yr == year::junior) out << " Junior ";
   else if (yr == year::senior) out << " Senior ";
   else if (yr == year::grad) out << " Grad ";
   
   return out;
}

enum class support {ta, ra, fellowship, other};

ostream& operator<<(ostream& out, const support & s)
{
   if (s == support::ta) out << " TA ";
   else if (s == support::ra) out << " RA ";
   else if (s == support::fellowship) out << " Fellowship ";
   else if (s == support::other) out << " Other ";
   
   return out;
}







class grad_student: public student {
public:
   grad_student
      (string  nm, int id, double g, year x, support t, string d, string th); 
   void print()const;
protected:
   support      s;
   string       dept;
   string       thesis;
};

student::student(string nm, int id, double g, year x)
		:student_id(id), gpa(g), y(x) , name(nm) { }

grad_student::grad_student(
   string nm, int id, double g, year x, 
   support t, string d, string th) 
   :student(nm, id, g, x), s(t), dept(d), thesis(th) { }

void student::print() const
{
   cout << "\n" << name << " , " << student_id << " , " 
	<< y << " , " << gpa << endl;
}

void grad_student::print()const
{
   student::print();    //base class information is printed
   cout << dept << " , " << s << "\n" << thesis << endl;
}

//Test pointer conversion rules.

int main()
{
   student        s("Mae Pohl", 100, 3.425, year::fresh), *ps = &s;
   grad_student   gs("Morris Pohl", 200, 3.2564, 
		     year::grad, support::ta, "Pharmacy",
		    "Retail Pharmacies"), *pgs;

   ps -> print();     //student::print
   ps = pgs = &gs;
   ps -> print();     //grad_student::print
   pgs -> print();    //grad_student::print
}

