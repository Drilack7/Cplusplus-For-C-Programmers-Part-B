// OOP = ADT + inheritence + dynamic typing

#include <iostream>
#include <memory>   //use shared_pointer
#include <string>
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;


class Tree;

class Node {  //abstract base class
protected:
   virtual void print(ostream& o)const=0;
   virtual int eval() const = 0;
   virtual ~Node() {}     //note virtual destructor
private:
   friend class Tree;
   friend ostream& operator<<(ostream&, const Tree&);
};

class Tree {
public:
   Tree(int);                //constant
   int eval()const {return p->eval();}
private:
   friend ostream& operator<<(ostream&, const Tree&);
   std::shared_ptr<Node> p;  //polymorphic hierarchy
};


ostream& operator<<(ostream& o, const Tree& t)
{
   t.p -> print(o);
   return (o);
}


class IntNode: public Node {
private:
   virtual void print(ostream& o)const { o << n ;}
   virtual int eval()const{ return n;}
   friend class Tree;
   int n;
   IntNode(int k): n (k) {}
};


Tree::Tree(int n): p( new IntNode(n)){ }

int main()
{

   Tree t1 = Tree(4);
   Tree t2 = Tree(44);
   cout << "t1 = " << t1 << " ;  t2 = " << t2 << endl;
   cout << "t1:" << t1.eval() << "  t2:" << t2.eval() << endl;
}

