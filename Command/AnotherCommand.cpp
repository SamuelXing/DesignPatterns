#include<iostream>
#include<vector>

class Number
{
public:
	void dubble(int& value)
	{
		value *= 2;
	}
private:

};

class Command
{
public:
	virtual void execute(int &) = 0;
};

class SimpleCommand: public Command
{
private:
	typedef void(Number:: *Action)(int&);
	Number* receiver;
	Action action;
public:
	SimpleCommand(Number* rec, Action act)
	{
		receiver = rec;
		action = act;
	}
	void execute(int& num)
	{
		(receiver->*action)(num);
	}
};

class MacroCommand: public Command
{
private:
	std::vector<Command*> list;
public:
	void add(Command* cmd)
	{
		list.push_back(cmd);
	}
	void execute(int& num)
	{
		for(int i=0; i< list.size(); i++)
		{
			list[i]->execute(num);
		}
	}
};

int main()
{
	Number object;
	Command* commands[3];
	SimpleCommand sp = SimpleCommand(&object, &Number::dubble);
	commands[0] = &sp;
	
	MacroCommand two;
	two.add(commands[0]);
	two.add(commands[0]);
	commands[1] = &two;
	
	MacroCommand four;
	four.add(&two);
	four.add(&two);
	commands[2] = &four;

	int num, index;
	while(true)
	{
		std::cout << "Enter number selection (0=2x 1=4x, 2=16x): ";
		std::cin >> num >> index;
		commands[index]->execute(num);
		std::cout << " " << num << "\n";
	}

}



