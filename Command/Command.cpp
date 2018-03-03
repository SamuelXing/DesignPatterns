/*
 * Command
 * =======
 * Intent:
 * 1, Encapsulate a request as an object, thereby letting you parametrize clients with different requests, queue or log requests, and support undoable operations.
 * 2, Promote "invocation of a method on an object" to full object status
 * 3, An object-oriented callback
 *
 * Structure:
 * 1, The client that creates a command is not the same client that executes it. This separation provides flexibility in the timing and sequencing of commands. 
 * Materializing commands as objects means they can be passed, staged, shared, loaded in a table, and otherwise instrumented or manipulated like any other object.
 * 2, Command objects can be thought of as "tokens" that are created by one client that knows what need to be done, and passed to another client that has the resources for doing it.
 *
 *
 * */

#include<iostream>
#include<string>
class Person;

class Command
{
private:
	// 1. Create a class that encapsulates an object and a member function
	// a pointer to a member function (the attribute's name is "method")
	Person* object;
	void(Person::*method)();
public:
	Command(Person* obj = 0, void(Person::*meth)() = 0)
	{
		object = obj; // the argument's name is "meth"
		method = meth;
	}
	void execute()
	{
		(object->*method)(); // invoke the method on the object
	}
};

class Person
{
private:
	std::string name;
	// cmd is a "black box", it is a method invocation
	// promoted to "full object status"
	Command cmd;
public:
	Person(std::string n, Command c): cmd(c)
	{
		name = n;
	}
	void talk()
	{
		// "this" is the sender, cmd has the receiver
		std::cout << name << " is talking" << std::endl;
		cmd.execute(); // ask the "black box" to callback the receiver
	}
	void passOn()
	{
		std::cout << name << "is passing on" << std::endl;
		// 4. When the sender is ready to callback to the receiver,
		cmd.execute();
	}
	void gossip()
	{
		std::cout << name << " is gossiping" << std::endl;
		cmd.execute();
	}
	void listen()
	{
		std::cout << name << " is listening" << std::endl;
	}
};

int main()
{
	// Fred will "execute" Barney which will result in a call to passOn()
	// Barney will "execute" Betty which will result in a call to gossip()
	// Betty will "execute" Wilma which will result in a call to listen()
	Person wilma("wilma", Command());
	// 2. Instantiate an object for each "callback"
	// 3. Pass each object to its future "sender"
	Person betty("Betty", Command(&wilma, &Person::listen));
	Person barney("Barney", Command(&betty, &Person::gossip));
	Person fred("Fred", Command(&barney, &Person::passOn));
	fred.talk();
}







