/*
 * Observer
 * ========
 * Intent:
 * 1, Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.
 * 2, Encapsulate the core (or common or engine) components in a Subject abstraction, and the variable (or optional or user interface) components in an Observer hierarchy.
 * 3, The "View" part of Model-View-Controller.
 *
 * Structure:
 * 1, Subject represents the core (or independent or common or engine) abstraction. 
 * 2, Observer represents the variable (or dependent or optional or user interface) abstraction. 
 * 3, The Subject prompts the Observer objects to do their thing. Each Observer can call back to the Subject as needed.
 *
 *
 * */

#include<iostream>
#include<vector>

class Observer
{
public:
	virtual void update(int value) = 0;
};

class Subject
{
private:
	int m_value;
	std::vector<Observer*> m_views;
public:
	void attach(Observer* obs)
	{
		m_views.push_back(obs);
	}
	void set_val(int value)
	{
		m_value = value;
		notify();
	}
	void notify()
	{
		for(int i=0; i< m_views.size();++i)
			m_views[i]->update(m_value);
	}
};

class DivObserver: public Observer
{
private:
	int m_div;
public:
	DivObserver(Subject* model, int div)
	{
		model->attach(this);
		m_div = div;
	}
	void update(int v)
	{
		std::cout << v << " div " << m_div << " is " << v / m_div << '\n';
	}
};

class ModObserver: public Observer
{
private:
	int m_mod;
public:
	ModObserver(Subject* model, int mod)
	{
		model->attach(this);
		m_mod = mod;
	}
	void update(int v)
	{
		std::cout << v << " mod " << m_mod << " is " << v%m_mod << "\n";
	}
};

int main()
{
	Subject subj;
	DivObserver divObs1(&subj, 4);
	DivObserver divObs2(&subj, 3);
	ModObserver modObs3(&subj, 3);
	subj.set_val(14);
}




