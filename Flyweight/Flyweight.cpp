/*
 * Flyweight
 * =========
 * Intent:
 * 1, Use sharing to support large numbers of fine-grained objects efficiently.
 * 2, The Motif GUI strategy of replacing heavy-weight widgets with light-weight gadgets.
 *
 * Structure:
 * 1, Flyweights are stored in a Factory's repository. 
 * 2, The client restrains herself from creating Flyweights directly, and requests them from the Factory.
 * 3, Each Flyweight cannot stand on its own.
 * 4, Any attributes that would make sharing impossible must be supplied by the client whenever a request is made of the Flyweight. 
 * 5, If the context lends itself to "economy of scale" (i.e. the client can easily compute or look-up the necessary attributes), then the Flyweight pattern offers appropriate leverage.
 * */

#include<iostream>
class Gazillion
{
public:
	Gazillion(int value_one)
	{
		m_value_one = value_one;
		std::cout << "ctor: " << m_value_one << "\n";
	}
	~Gazillion()
	{
		std::cout << m_value_one << " ";
	}
	void report(int value_two)
	{
		std::cout << m_value_one << value_two << " ";
	}
private:
	int m_value_one;
};

class Factory
{
public:
	static Gazillion* get_fly(int in)
	{
		if(!s_pool[in])
			s_pool[in] = new Gazillion(in);
		return s_pool[in];
	}

	static void clean_up()
	{
		std::cout << "dtors: ";
		for(int i=0; i < X; i++)
		{
			if(s_pool[i])
				delete s_pool[i];
		}
		std::cout << "\n";
	}
	static int X, Y;
private:
	static Gazillion* s_pool[];
};

int Factory::X = 6, Factory::Y = 10;
Gazillion* Factory::s_pool[] = 
{
	0,0,0,0,0,0
};

int main()
{
	for(int i =0; i< Factory::X; ++i)
	{
		for(int j=0; j< Factory::Y; j++)
		{
			Factory::get_fly(i)->report(j);
		}
		std::cout << "\n";
	}
	Factory::clean_up();
}



