#ifndef _INTRODUCTIONSTATE_h
#define _INTRODUCTIONSTATE_h

#include "State.h"

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;

class IntroductionState : public State
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;

	char* _companyName = "SHARP METAL";
	char* _programName = "HOP-15";
	char* _machineAuthor = "SYLWESTER MILOS";
	char* _info = "WCISNIJ PRZYCISK";

public:
	virtual void init();
	virtual void react();
	virtual void reset();

	char* getCompanyName() { return _companyName; };
	char* getProgramName() { return _programName; };
	char* getMachineAuthor() { return _machineAuthor; };
	char* getInfo() { return _info; };
};

#endif

