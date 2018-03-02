/*
 * Facade
 * ======
 * Intent:
 * 1, Provide a unified interface to a set of interfaces in a subsystem. Facade defines a higher-level interface that makes the subsystem easier to use.
 * 2, Wrap a complicated subsystem with a simpler interface.
 *
 * Structure:
 * Facade takes a "riddle wrapped in an enigma shrouded in mystery", and interjects a wrapper that tames the amorphous and inscrutable mass of software.
 *
 * */

#include<iostream>
class MisDepartment
{
public:
	void submitNetworkRequest()
	{
		_state = 0;
	}
	bool checkOnStatus()
	{
		_state++;
		if(_state == Complete)
			return true;
		return false;
	}
private:
	enum States
	{
		Received, DenyAllKnowledge, ReferClientToFacilities,
		FacilitiesHasNotSentPaperwork, ElectricianIsNotDone,
		ElectricianDidItWrong, DispatchTechnician, SignedOff, DoesNotWork,
		FixElectriciansWiring, Complete
	};
	int _state;
};

class ElectricianUnion
{
public:
	void submitNetworkRequest()
	{
		_state = 0;
	}
	bool checkOnStatus()
	{
		_state++;
		if(_state == Complete)
			return true;
		return false;
	}
private:
	enum States
	{
		Received, RejectTheForm, SizeTheJob, SmokeAndJokeBreak,
		WaitForAuthorization, DoTheWrongJob, BlameTheEngineer, WaitToPunchOut,
		DoHalfAJob, ComplainToEngineer, GetClarification, CompleteTheJob,
		TurnInThePaperwork, Complete
	};
	int _state;
};

class FacilitiesDepartment
{
public:
	void submitNetworkRequest()
	{
		_state = 0;
	}
	bool checkOnStatus()
	{
		_state++;
		if(_state == Complete)
			return true;
		return false;
	}
private:
	enum States{
		Received, AssignToEngineer, EngineerResearches, RequestIsNotPossible,
		EngineerLeavesCompany, AssignToNewEngineer, NewEngineerResearches,
		ReassignEngineer, EngineerReturns, EngineerResearchesAgain,
		EngineerFillsOutPaperWork, Complete
	};
	int _state;
};


class FacilitiesFacade
{
public:
	FacilitiesFacade()
	{
		_count = 0;
	}
	
	void submitNetworkRequest()
	{
		_state = 0;
	}

	bool checkOnStatus()
	{
		_count++;
		/* Job request has just been received */
		if(_state == Received)
		{
			_state++;
			/* Forward the job request to the engineer */
			_engineer.submitNetworkRequest();
			std::cout << "submitted to Facilities - " << _count 
							<< " phone calles so far" << std::endl;
		}
		else if(_state == SubmitToEngineer)
		{
			/* If engineer is complete, forward to electrician */
			if(_engineer.checkOnStatus())
			{
				_state++;
				_electrician.submitNetworkRequest();
				std::cout << "submitted to Electrician - " << _count 
								<< " phone calls so far" << std::endl;
			}
		}
		else if(_state == SubmitToElectrician)
		{
			 /* If electrician is complete, forward to technician */
			if(_electrician.checkOnStatus())
			{
				_state++;
				_technician.submitNetworkRequest();
				std::cout << "submitted to MIS - " << _count <<
								" phone calls so far" << std::endl;
			}
		}
		else if(_state == SubmitToTechnician)
		{
			/* If technician is complete, job is done */
			if(_technician.checkOnStatus())
							return true;
		}
		return false;
	}

	int getNumberOfCalls()
	{
		return _count;
	}
private:
	enum States
	{
		Received, SubmitToEngineer, SubmitToElectrician, SubmitToTechnician
	};
	int _state;
	int _count;
	FacilitiesDepartment _engineer;
	ElectricianUnion _electrician;
	MisDepartment _technician;
};

int main()
{
	FacilitiesFacade facilities;

	facilities.submitNetworkRequest();
	/* Keep checking until job is complete */
	while(!facilities.checkOnStatus())
					;
	std::cout << "job completed after only " << facilities.getNumberOfCalls() 
					<< " phone calls" << std::endl;
}






