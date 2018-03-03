#include<iostream>
#include<vector>

class AlarmListener
{
public:
	virtual void alarm() = 0;
};

class SensorSystem
{
private:
	std::vector<AlarmListener*> listeners;
public:
	void attach(AlarmListener* al)
	{
		listeners.push_back(al);
	}
	void soundTheAlarm()
	{
		for(int i=0; i< listeners.size(); i++)
		{
			listeners[i]->alarm();
		}
	}
};

class Lighting: public AlarmListener
{
public:
	void alarm()
	{
		std::cout << "Lights up" << '\n';
	}
}
;

class Gates: public AlarmListener
{
public:
	void alarm()
	{
		std::cout << "gates close\n"; 
	}
};

class CheckList
{
private:
	virtual void localize()
	{
		std::cout << "	establish a perimeter\n";
	}
	virtual void isolate()
	{
		std::cout << "	isolate the grid\n";
	}
	virtual void identify()
	{
		std::cout << "	identify the source\n";
	}
public:
	void byTheNumbers()
	{
		// Template Method design pattern
		localize();
		isolate();
		identify();
	}
};

// class inheri.  // type inheritance
class Surveillance: public CheckList, public AlarmListener
{
private:
	void isolate()
	{
		std::cout << "	train the cameras\n"; 
	}
public:
	void alarm()
	{
		std::cout << "Surveillance - by the numbers:\n";
		byTheNumbers();
	}
};

int main()
{
	SensorSystem ss;
	Gates g = Gates();
	Lighting l = Lighting();
	Surveillance s = Surveillance();
	ss.attach(&g);
	ss.attach(&l);
	ss.attach(&s);
	ss.soundTheAlarm();
}





