/*
 * Bridge
 * ======
 * Intent:
 * 1, Decouple an abstraction from its implementation so that the two can vary independently.
 * 2, Publish interface in an inheritance hierarchy, and bury implementation in its own inheritance hierarchy.
 * 3, Beyond encapsulation, to insulation
 *
 * Motivation:
 * Consider the domain of "thread scheduling".
 * There are two types of thread schedulers, and two types of operating systems or "platforms". Given this approach to specialization, we have to define a class for each permutation of these two dimensions. 
 * Structure:
 * 1, The Client doesn't want to deal with platform-dependent details. The Bridge pattern encapsulates this complexity behind an abstraction "wrapper".
 * 2, Bridge emphasizes identifying and decoupling "interface" abstraction from "implementation" abstraction.
 *
 * */

#include<iostream>
#include<string>
#include<iomanip>

class TimeImp{
public:
	TimeImp(int hr, int min){
		hr_ = hr;
		min_ = min;
	}
	virtual void tell(){
		std::cout << "time is "<< hr_ << " " << min_ << " "<< std::endl;
	}

protected:
	int hr_, min_;
};

class CivilianTimeImp: public TimeImp {
public:
	CivilianTimeImp(int hr, int min, int pm): TimeImp(hr, min) {
		if(pm)
			whichM_ = "PM";
		else
			whichM_ = "AM";
	}
	
	void tell() {
		std::cout << "time is "<< hr_ << " " << min_ << " "<< " " << whichM_ << std::endl;
	}
protected:
	std::string whichM_;
};

class ZuluTimeImp: public TimeImp{
public:
	ZuluTimeImp(int hr, int min, int zone): TimeImp(hr, min) {
		if(zone == 5)
			zone_ = "Easter Standard Time";
		else if(zone == 6)
			zone_ = "Central Standard Time";
	}

	void tell()
	{
		std::cout << "time is "<< hr_ << " " << min_ << " "<< zone_ << std::endl;
	}
protected:								
	std::string zone_;
};

class Time
{
public:
	Time(){}
	Time(int hr, int min){
		imp_ = new TimeImp(hr, min);	
	}

	virtual void tell()
	{
		imp_->tell();
	}
protected:
	TimeImp* imp_;
};

class CivilianTime: public Time {
public:
 CivilianTime(int hr, int min, int pm){
 	imp_ = new CivilianTimeImp(hr, min, pm);
 }
};

class ZuluTime: public Time {
public:
	ZuluTime(int hr, int min, int zone) {
		imp_ = new ZuluTimeImp(hr, min, zone);
	}
};

int main()
{
	Time* times[3];
	times[0] = new Time(14, 30);
	times[1] = new CivilianTime(2, 30, 1);
	times[2] = new ZuluTime(14, 30, 6);
	for(int i =0; i<3; i++)
		times[i]->tell();
}




