
#include<iostream>

class ExecuteInterface {
public:
	// 1. Specify the new interface
	virtual ~ExecuteInterface(){}
	virtual void execute() = 0;
};

// 2. Design a "wrapper" or "adapter" class
template<typename TYPE>
class ExecuteAdapter: public ExecuteInterface
{
public:
	ExecuteAdapter(TYPE* o, void(TYPE:: *m)())
	{
		object = o;
		method = m;
	}
	~ExecuteAdapter()
	{
		delete object;
	}
	
	 // 4. The adapter/wrapper "maps" the new to the legacy implementation
	 void execute()
	 {
		(object->*method)();
	 }
private:
	TYPE* object; // ptr-toobject attribute
	void(TYPE:: *method)(); /* the old */
};

// Three totally incompatible classes
class Fea {
public:
	~Fea()
	{
		std::cout << "Fea::dtor" << std::endl;
	}
	void doThis()
	{
		std::cout << "Fea::doThis()" << std::endl;
	}
};

class Feye {
public:
	~Feye()
	{
		std::cout << "Feye::dtor" << std::endl;
	}
	void doThat()
	{
		std::cout << "Feye::doThat()" << std::endl;
	}
};

class Pheau {
public:
	~Pheau()
	{
		std::cout << "Pheau::dtor" << std::endl;
	}
	void doTheOther()
	{
		std::cout << "Fea::doTheOther()" << std::endl;
	}
};

// The new is returned
ExecuteInterface** initialize()
{
	ExecuteInterface** array = new ExecuteInterface*[3];
	
	// the old is below
	array[0] = new ExecuteAdapter<Fea>(new Fea, &Fea::doThis);
	array[1] = new ExecuteAdapter<Feye>(new Feye, &Feye::doThat);
	array[2] = new ExecuteAdapter<Pheau>(new Pheau, &Pheau::doTheOther);
	return array;
}

int main()
{
	ExecuteInterface** objects = initialize();
	for(int i=0; i<3; i++)
	{
		objects[i]->execute();
	}

	//3, client used the new (ploymporphism)
	for(int i=0; i<3; i++)
	{
		delete objects[i];
	}
	delete objects;
	return 0;
}


