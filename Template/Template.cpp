/*
 * Template
 * ========
 * Intent:
 * 1, Define the skeleton of an algorithm in an operation, deferring some steps to client subclasses.
 * Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.
 * 2, Base class declares algorithm 'placeholders', and derived classes implement the placeholders.
 *
 * */

#include<iostream>

class Base
{
private:
	void a()
	{
		std::cout << "a ";
	}
	void c()
	{
		std::cout << "c ";
	}
	void e()
	{
		std::cout << "e ";
	}
	// 2. Steps requiring peculiar implementations are "placeholders" in base class
	virtual void ph1() = 0;
	virtual void ph2() = 0;
public:
	// 1. Standardize the skeleton of an algorithm in a base class "template method"
	void execute()
	{
		a();
		ph1();
		c();
		ph2();
		e();
	}
};

class One: public Base
{
	// 3. Derived classes implement placeholder methods
	void ph1()
	{
		std::cout << "b ";
	}
	void ph2()
	{
		std::cout << "d ";
	}
};

class Two: public Base
{
	void ph1()
	{
		std::cout << "2 ";
	}
	void ph2()
	{
		std::cout << "4 ";
	}
};

int main()
{
	Base* array[] = 
	{
		new One(), new Two()
	};
	
	for(int i = 0; i<2; i++)
	{
		array[i]->execute();
		std::cout << "\n";
	}
}





