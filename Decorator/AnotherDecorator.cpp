#include<iostream>

// 1. "lowest common denominator"
class Widget
{
public:
	virtual void draw() = 0;
};

class TextField: public Widget
{
private:
	int width, height;
public:
	TextField(int w, int h)
	{
		width = w;
		height = h;
	}

	void draw()
	{
		std::cout << "TextField: " << width << ", " << height << "\n";
	}
};

// 2. 2nd level base class
class Decorator: public Widget // 4. "is a" relationship
{
private:
	Widget* wid; // 4. "has a" relationship
public:
	Decorator(Widget* w)
	{
		wid = w;
	}

	void draw()
	{
		wid->draw(); // 5.Delegation
	}
};

class BorderDecorator: public Decorator
{
public:
	// 6. Optional embellishment
	BorderDecorator(Widget* w): Decorator(w){}

	void draw()
	{
		// 7. Delegate to base class and add extra stuff
		Decorator::draw();
		std::cout << "	BorderDecorator\n"; 
	}
};


class ScrollDecorator: public Decorator
{
public:
	// 6. Optional embellishment
	ScrollDecorator(Widget* w):Decorator(w){}

	void draw()
	{
		// 7. Delegate to base class and add extra stuff
		Decorator::draw();
		std::cout << "	ScrollDecorator\n";		
	}
};

int main()
{
	// 8. Client has the responsibility to compose desired configurations
	Widget* awidget = new BorderDecorator(new BorderDecorator(new ScrollDecorator(new TextField(80, 24))));
	awidget->draw();
}









