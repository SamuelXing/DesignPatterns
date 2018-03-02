/*
 * Composite
 * =========
 * Intent:
 * 1, Compose objects into tree structures to represent whole-part hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.
 * 2, Recursive composition
 * 3, "Directories contain entries, each of which could be a directory."
 * 4, 1-to-many "has a" up the "is a" hierarchy
 *
 * Structure:
 * Composites that contain Components, each of which could be a Composite.
 * */

#include<iostream>
#include<vector>

// 2. Create an "interface" (lowest common denominator)
class Component
{
public:
	virtual void traverse() = 0;
};

class Leaf: public Component
{
// 1. Scalar class   3. "isa" relationship
private:
	int value;
public:
	Leaf(int val)
	{
		value = val;
	}
	void traverse()
	{
		std::cout << value << " ";
	}
};

class Composiste: public Component
{
 // 1. Vector class   3. "isa" relationship
private:
	std::vector<Component*> children; // 4. "container" coupled to the interface
public:
	// 4. "container" class coupled to the interface
	void add(Component* ele)
	{
		children.push_back(ele);
	}
	void traverse()
	{
		for(int i=0; i< children.size(); i++){
		// 5. Use polymorphism to delegate to children
			children[i]->traverse();
		}
	}
};

int main()
{
	Composiste containers[4];
	
	for(int i=0; i<4;i++)
	{
		for(int j=0; j<3;j++){
			containers[i].add(new Leaf(i*3+j));
		}
	}

	for(int i=1; i<4;i++){
		containers[0].add(&containers[i]);
	}

	for(int i=0; i<4; i++){
		containers[i].traverse();
		std::cout << std::endl;
	}
}





