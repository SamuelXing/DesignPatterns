/*
 * State
 * ====
 * Intent:
 * 1, Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.
 * 2, An object-oriented state machine
 * 3, wrapper + polymorphic wrappee + collaboration
 *
 * Structure:
 * 1, The state machine's interface is encapsulated in the "wrapper" class. 
 * 2, The wrappee hierarchy's interface mirrors the wrapper's interface with the exception of one additional parameter. 
 * 3, The extra parameter allows wrappee derived classes to call back to the wrapper class as necessary. 
 * 4, Complexity that would otherwise drag down the wrapper class is neatly compartmented and encapsulated in a polymorphic hierarchy to which the wrapper object delegates.
 *
 * */

#include<iostream>

class Machine
{
 class State* current;
public:
 Machine();
 void setCurrent(State* s)
 {
 	current = s;
 }
 void on();
 void off();
};

class State
{
public:
	virtual void on(Machine* m)
	{
		std::cout << "	already ON\n";
	}
	virtual void off(Machine* m)
	{
		std::cout << "	already OFF\n";
	}
};

void Machine::on()
{
	current->on(this);
}

void Machine::off()
{
	current->off(this);
}

class ON: public State
{
public:
	ON()
	{
		std::cout << "	ON-ctor ";
	}
	~ON()
	{
		std::cout << "	dtor-ON\n";
	}
	void off(Machine* m);
};

class OFF: public State
{
public:
	OFF()
	{
		std::cout << "	OFF-ctor ";
	}
	~OFF()
	{
		std::cout << "	dtor-OFF\n";
	}
	void on(Machine* m)
	{
		std::cout << "	going from OFF to ON";
		m->setCurrent(new ON());
		delete this;
	}
};

void ON::off(Machine* m)
{
	std::cout << "	going from ON to OFF";
	m->setCurrent(new OFF());
	delete this;
}

Machine::Machine()
{
	current = new OFF();
	std::cout << "\n";
}

int main()
{
	Machine fsm;
	void(Machine::*ptrs[])() = 
	{
		&Machine::off, &Machine::on
	};
	int num;
	while(1)
	{
		std::cout << "Enter 0/1:";
		std::cin >> num;
		(fsm.*ptrs[num])();
	}
}




