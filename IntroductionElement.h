#ifndef _INTRODUCTIONELEMENT_h
#define _INTRODUCTIONELEMENT_h

#include "Element.h"
#include "lcd.h"
#include "simpleKeypad.h"

class IntroductionElement : public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;

	char* _companyName = "SHARP METAL";
	char* _programName = "HOP-15";
	char* _machineAuthor = "SYLWESTER MILOS";
	char* _info = "WCISNIJ PRZYCISK";

public:
	IntroductionElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad);

	virtual void react();

	char* getCompanyName() { return _companyName; };
	char* getProgramName() { return _programName; };
	char* getMachineAuthor() { return _machineAuthor; };
	char* getInfo() { return _info; };
};

#endif

