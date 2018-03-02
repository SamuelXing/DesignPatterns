#include<iostream>
#include<string>

class Person
{
private:
	std::string nameString;
	static std::string list[];
	static int next;
public:
	Person()
	{
		nameString = list[next++];
	}
	std::string name()
	{
		return nameString;
	}
};

std::string Person::list[] = 
{
	"Tom", "Dick", "Harry", "Bubba"
};

int Person::next = 0;

class PettyCashProtected
{
private:
	int balance;
public:
	PettyCashProtected()
	{
		balance = 500;
	}
	bool withdraw(int amount)
	{
		if(amount > balance)
			return false;
		balance -= amount;
		return true;
	}
	int getBalance()
	{
		return balance;
	}
};

class PettyCash
{
private:
	PettyCashProtected realThing;
public:
	bool withdraw(Person& p, int amount)
	{
		if (p.name() == "Tom" || p.name() == "Harry" || p.name() == "Bubba")
			return realThing.withdraw(amount);
		else
			return false;
	}
	int getBalance()
	{
		return realThing.getBalance();
	}
};

int main()
{
	PettyCash pc;
	Person workers[4];
	for(int i=0, amount = 100; i<4; i++, amount += 100)
		if(!pc.withdraw(workers[i], amount))
			std::cout << "No money for " << workers[i].name() << '\n';
		else
			std::cout << amount << " dollars for " << workers[i].name() << "\n";
	std::cout << "Remaining balance is " << pc.getBalance() << "\n";
}
