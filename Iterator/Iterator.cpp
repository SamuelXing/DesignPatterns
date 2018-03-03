/*
 * Iterator
 * =======
 * Intent:
 * 1, Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
 * 2, The C++ and Java standard library abstraction that makes it possible to decouple collection classes and algorithms.
 * 3, Promote to "full object status" the traversal of a collection.
 * 4, Polymorphic traversal 
 * 
 * Structure:
 * The Client uses the Collection class' public interface directly. But access to the Collection's elements is encapsulated behind the additional level of abstraction called Iterator. 
 * Each Collection derived class knows which Iterator derived class to create and return. 
 * After that, the Client relies on the interface defined in the Iterator base class.
 *
 * */

#include<iostream>

class Stack
{
private:
	int items[10];
	int sp;
public:
	friend class StackIter;
	Stack()
	{
		sp = -1;
	}
	void push(int in)
	{
		items[++sp] = in;
	}
	int pop()
	{
		return items[sp--];
	}
	bool isEmpty()
	{
		return (sp==-1);
	}
};

class StackIter
{
private:
	const Stack& stk;
	int index;
public:
	StackIter(const Stack& s): stk(s)
	{
		index = 0;
	}
	void operator++()
	{
		index ++;
	}
	bool operator()()
	{
		return index != stk.sp + 1;
	}
	int operator*()
	{
		return stk.items[index];
	}
};

bool operator==(const Stack& l, const Stack& r)
{
	StackIter itl(l), itr(r);
	for(; itl(); ++itl, ++ itr)
	{
		if(*itl != *itr)
			break;
	}
	return !itl() && !itr();
}

int main()
{
  Stack s1;
  int i;
  for (i = 1; i < 5; i++)
    s1.push(i);
  Stack s2(s1), s3(s1), s4(s1), s5(s1);
  s3.pop();
  s5.pop();
  s4.push(2);
  s5.push(9);
  std::cout << "1 == 2 is " << (s1 == s2) << std::endl;
  std::cout << "1 == 3 is " << (s1 == s3) << std::endl;
  std::cout << "1 == 4 is " << (s1 == s4) << std::endl;
  std::cout << "1 == 5 is " << (s1 == s5) << std::endl;
}



