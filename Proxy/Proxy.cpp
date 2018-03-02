/*
 * Proxy Design Pattern
 * ====================
 * Intent:
 * 1, Provide a surrogate or placeholder for another object to control access to it.
 * 2, Use an extra level of indirection to support distributed, controlled, or intelligent access.
 * 3, Add a wrapper and delegation to protect the real component from undue complexity.
 *
 * Structure:
 * By defining a Subject interface, the presence of the Proxy object standing in place of the RealSubject is transparent to the client.
 *
 * */

#include<iostream>
#include<string>
class Subject
{
public:
	virtual void execute() = 0;
private:
};


class RealSubject: public Subject
{
private:
	std::string str;
public:
	RealSubject(const std::string& s)
	{
		str = s;
	}
	void execute()
	{
		std::cout << str << "\n";
	}
};

class ProxySubject: public Subject
{
private:
	std::string first, second, third;
	RealSubject* ptr;
public:
	ProxySubject(std::string s)
	{
		int num = s.find_first_of(' ');
		first = s.substr(0, num);
		s = s.substr(num+1);
		num = s.find_first_of(' ');
		second = s.substr(0, num);
		s=s.substr(num+1);
		third = s.substr(0, num);
		s= s.substr(num+1);
		ptr = new RealSubject(s);
	}
	~ProxySubject()
	{
		delete ptr;
	}
	RealSubject* operator->()
	{
		std::cout << first << " " << second << " ";
		return ptr;
	}
	void execute()
	{
		std::cout << first << " " << third << " ";
		ptr->execute();
	}
};

int main()
{
  ProxySubject obj(std::string("the quick brown fox jumped over the dog"));
  obj->execute();
  obj.execute();
}




