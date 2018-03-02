/*
 * Adapter
 * ======
 * Intent:
 * 1, Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.
 * 2, Wrap an existing class with a new interface.
 * 3, Impedance match an old component to a new system
 *
 * Usages:
 * Adapter is about creating an intermediary abstraction that translates, or maps, the old component to the new system. 
 * Clients call methods on the Adapter object which redirects them into calls to the legacy component. This strategy can be implemented either with inheritance or with aggregation.
 * 
 * */


#include<iostream>

typedef int Coordinate;
typedef int Dimension;

// Desired interface
class Rectangle
{
public:
	virtual void draw() = 0;
};

// Legacy component
class LegacyRectangle
{
public:
	LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
	{
		x1_ = x1;
		y1_ = y1;
		x2_ = x2;
		y2_ = y2;
		std::cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
																						          << x2_ << "," << y2_ << ")" << std::endl;
	}
	void oldDraw()
	{
		std::cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ << 
				") => (" << x2_ << "," << y2_ << ")" << std::endl;
	}
private:
	Coordinate x1_;
	Coordinate y1_;
	Coordinate x2_;
	Coordinate y2_;
};

// Adapter wrapper
class RectangleAdapter: public Rectangle, private LegacyRectangle
{
public:
	RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h): 
					LegacyRectangle(x,y,x+w,y+h){
		std::cout << "RectangleAdapter: create.  (" << x << "," << y << 
						          "), width = " << w << ", height = " << h << std::endl;
	}

	virtual void draw()
	{
		std::cout << "RectangleAdapter: draw." << std::endl;
		oldDraw();
	}
};

int main()
{
	Rectangle* r = new RectangleAdapter(120, 200, 60, 40);
	r->draw();
}



