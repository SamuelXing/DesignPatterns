/*
 * Decorator
 * ========
 * Intent:
 * 1, Attach additional responsibilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending functionality.
 * 2, Client-specified embellishment of a core object by recursively wrapping it.
 * 3, Wrapping a gift, putting it in a box, and wrapping the box.
 *
 * */

#include<iostream>
class I {
public:
	virtual ~I(){}
	virtual void do_it() = 0;
};

class A: public I{
public:
	~A(){
		std::cout << "A dtor" << "\n";
	}
	void do_it() {
		std::cout << "A\n";
	}
};

class D: public I{
public:
	D(I* inner){
		m_wrapper = inner;
	}
	~D(){
		delete m_wrapper;
	}
	void do_it(){
		std::cout << "do OpD() \n";
		m_wrapper->do_it();
	}
private:
	I* m_wrapper;
};


int main(){
	I* insD = new D(new A);
	insD->do_it();
	delete insD;
}



