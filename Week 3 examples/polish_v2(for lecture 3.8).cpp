#include <iostream>
using namespace std;


int valtab[127] ; //used for integer values of variables
class Tree;
class Node {
protected:
   Node(){ use = 1; }
   virtual void print(ostream&) = 0;
   virtual ~Node() {}     //note virtual destructor
   virtual int eval() = 0;
private:
   friend class Tree;
   friend ostream& operator<<(ostream&, const Tree&);
   int use;    //reference count
};

class Tree {
public:
   Tree(int);                //constant
   Tree(const char);               //variable
   Tree(const char, Tree);        //unary operator
   Tree(const char, Tree, Tree);  //binary operator
   Tree(const Tree& t) { p = t.p; ++p -> use;}
   ~Tree() {if (--p ->use == 0) delete p; }
   void operator=(const Tree& t);
   int eval() {return p->eval();}
private:
   friend class Node;
   friend ostream& operator<<(ostream&, const Tree&);
   Node* p;  //polymorphic hierarchy
};

void Tree:: operator=(const Tree& t)
{
   ++t.p -> use;
   if ( --p -> use == 0)
      delete p;
   p = t.p;
}

ostream& operator<<(ostream& o, const Tree& t)
{
   t.p -> print(o);
   return (o);
}

class LeafNode: public Node {
private:
   friend class Tree;
   void print(ostream& o) = 0;
   virtual int eval() = 0;
};

class IntNode: public LeafNode {
public:
   int eval(){ return n;}
private:
   friend class Tree;
   int n;
   void print(ostream& o) { o << n ;}
   IntNode(int k): n (k) {}
};

class IdNode: public LeafNode {
public:
   int eval(){ return valtab[name];}
private:
   friend class Tree;
   char name;
   void print(ostream& o) { o << name ;}
   IdNode(const char id): name (id) {}
};

class UnaryNode: public Node {
public:
   int eval();
private:
   friend class Tree;
   char op;
   Tree opnd;
   UnaryNode(const char a, Tree b): op(a), opnd(b) {}
   void print (ostream& o) {o << "(" << op << opnd << ")";}
};

int UnaryNode::eval()
{
   switch (op){
   case '-': return (-opnd.eval());
   case '+': return (+opnd.eval());
   default: cerr << "no operand\n" << endl;
      return 0;
   }
}

class BinaryNode: public Node {
public:
   int eval();
private:
   friend class Tree;
   char op;
   Tree left;
   Tree right;
   BinaryNode(const char a, Tree b, Tree c): op(a), left(b), right(c){}
   void print (ostream& o) {o << "(" << left << op << right << ")";}
};

int BinaryNode::eval()
{
   switch (op){
   case '-': return (left.eval() - right.eval());
   case '+': return (left.eval() + right.eval());
   case '*': return (left.eval() * right.eval());
   default: cerr << "no operand\n" << endl;
      return 0;
   }
}


Tree::Tree(int n)
{
   p = new IntNode(n);
}

Tree::Tree(const char id)
{
   p = new IdNode(id);
}

Tree::Tree(const char op, Tree t)
{
   p = new UnaryNode(op, t);
}

Tree::Tree(const char op, Tree left, Tree right)
{
   p = new BinaryNode(op, left, right);
}

int main()
{

   valtab['A'] = 3; valtab['B'] = 4;
   cout << "A = 3,  B = 4" << endl;
   Tree t1 = Tree('*', Tree('-', 5), Tree('+', 'A', 4));
   Tree t2 = Tree('+', Tree('-', 'A', 1), Tree('+', t1, 'B'));
   cout << "t1 = " << t1 << " ;  t2 = " << t2 << endl;
   cout << "t1:" << t1.eval() << "  t2:" << t2.eval() << endl;
}

