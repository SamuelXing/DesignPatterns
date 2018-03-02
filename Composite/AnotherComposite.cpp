#include<iostream>
#include<vector>

class Component
{
public:
	virtual void traverse() = 0;
};

class Primitive: public Component
{
private:
	int value;
public:
	Primitive(int val)
	{
		value = val;
	}
	void traverse()
	{
		std::cout << value << " ";
	}
};

class Composite: public Component
{
private:
	std::vector<Component*> children;
	int value;
public:
	Composite(int val){
		value = val;
	}
	void add(Component* c){
		children.push_back(c);
	}
	void traverse(){
		std::cout << value << " ";
		for(int i=0; i< children.size(); i++)
		{
			children[i]->traverse();
		}
	}
};

class Row: public Composite
{
public:
	// Two different kinds of "container" classes.
	// Most of the "meat" is in the Composite base class
	Row(int val):Composite(val){}
	void traverse(){
		std::cout << "Row";
		Composite::traverse();
	}
};

class Column: public Composite
{
public:
	Column(int val): Composite(val){}
	void traverse()
	{
		std::cout << "Col";
		Composite::traverse();
	}
};

int main()
{
	Row first(1);
	Column second(2);
	Column third(3);
	Row fourth(4);
	Row fifth(5);
	first.add(&second);
	first.add(&third);
	third.add(&fourth);
	third.add(&fifth);
	Primitive p1(6);
	Primitive p2(7);
	Primitive p3(8);
	Primitive p4(9);
	Primitive p5(10);
	first.add(&p1);
	second.add(&p2);
	third.add(&p3);
	fourth.add(&p4);
	fifth.add(&p5);
	first.traverse();
	std::cout << "\n";
}





