/*
 * Singleton
 * =========
 * Intent:
 * 1, Ensure a class has only one instance, and provide a global point of access to it.
 * 2, Encapsulated "just-in-time initialization" or "initialization on first use".
 * 
 * Structure:
 * Make the class of the single instance responsible for access and "initialization on first use". 
 * The single instance is a private static attribute. 
 * The accessor function is a public static method.
 * 
 * */

#include<iostream>
#include<string>

class Number
{
public:
	// 2. Define a public static accessor func
	static Number* instance();
	static void setType(const std::string& t)
	{
		type = t;
		delete inst;
		inst = NULL;
	}
	virtual void setValue(int in)
	{
		value = in;
	}
	virtual int getValue()
	{
		return value;
	}
protected:
	int value;
	// 4. Define all ctors to be protected
	Number()
	{
		std::cout << ":ctor: ";
	}

// 1. Define a private static attribute	
private:
	static std::string type;
	static Number* inst;
};

std::string Number::type = "decimal";
Number* Number::inst = 0;


class Octal: public Number
{
// 6. Inheritance can be supported
public:
	friend class Number;
	void setValue(int in)
	{
		value = in;
	}
protected:
	Octal(){}
};

Number* Number::instance()
{
	if(!inst){
		// 3. Do "lazy initialization" in the accessor function
		if(type == "octal"){
			inst = new Octal();
		}
		else{
			inst = new Number();
		}
	}
	return inst;
}

int main()
{
	// Number  myInstance; - error: cannot access protected constructor
	// 5. Clients may only use the accessor function to manipulate the Singleton
	Number::instance()->setValue(42);
	std::cout << "value is " << Number::instance()->getValue() << std::endl;
	Number::setType("octal");
	Number::instance()->setValue(64);
	std::cout << "value is " << Number::instance()->getValue() << std::endl;
}

