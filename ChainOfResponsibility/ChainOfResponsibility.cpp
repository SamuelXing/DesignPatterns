/*
 * ChainOfResponsibility
 * =====================
 * Intent:
 * 1, Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the chain until an object handles it.
 * 2, Launch-and-leave requests with a single processing pipeline that contains many possible handlers.
 * 3, An object-oriented linked list with recursive traversal.
 *
 * Structure:
 * 1, The derived classes know how to satisfy Client requests. If the "current" object is not available or sufficient, then it delegates to the base class, which delegates to the "next" object, and the circle of life continues.
 * 2, Multiple handlers could contribute to the handling of each request. The request can be passed down the entire length of the chain, with the last link being careful not to delegate to a "null next".
 *
 * */

#include<iostream>
#include<vector>
#include<ctime>

class Base
{
private:
	Base* next; // 1. "next" pointer in the base class
public:
	Base()
	{
		next = nullptr;
	}
	void setNext(Base* n)
	{
		next = n;
	}
	void add(Base* n)
	{
		if(next)
			next->add(n);
		else
			next = n;
	}
	// 2. The "chain" method in the base class always delegates to the next obj
	virtual void handle(int i)
	{
		next->handle(i);
	}
};


class Handler1: public Base
{
public:
	void handle(int i)
	{
		if(rand() % 3)
		{
			// 3. Don't handle requests 3 times out of 4
			std::cout << "H1 passed " << i << " ";
			Base::handle(i); // 3. Delegate to the base class
		}
		else
		{
			std::cout << "H1 handled " << i << " ";
		}
	}
};

class Handler2: public Base
{
public:
	void handle(int i)
	{
		if(rand() % 3)
		{
			// 3. Don't handle requests 3 times out of 4
			std::cout << "H2 passed " << i << " ";
			Base::handle(i); // 3. Delegate to the base class
		}
		else
		{
			std::cout << "H2 handled " << i << " ";
		}
	}
};


class Handler3: public Base
{
public:
	void handle(int i)
	{
		if(rand() % 3)
		{
			// 3. Don't handle requests 3 times out of 4
			std::cout << "H3 passed " << i << " ";
			Base::handle(i); // 3. Delegate to the base class
		}
		else
		{
			std::cout << "H3 handled " << i << " ";
		}
	}
};


int main()
{
	srand(time(0));
	Handler1 root;
	Handler2 two;
	Handler3 thr;
	root.add(&two);
	root.add(&thr);
	thr.setNext(&root);
	for(int i=1; i< 10; i++)
	{
		root.handle(i);
		std::cout << "\n";
	}
}








