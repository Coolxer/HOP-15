#ifndef program_h
#define program_h

#include "Input.h"
#include "Output.h"
#include "ElementManager.h"
#include "MenuElement.h"
#include "IntroductionElement.h"
#include "ProgramElement.h"

#include "SimpleKeypad.h"
#include "Lcd.h"
#include "SevSegms.h"
#include "Buzzer.h"
#include "StepperMotor.h"
#include "DcMotor.h"
#include "Endstop.h"
#include "Relay.h"

class Program
{
private:
	Lcd _lcd;
	SimpleKeypad _simpleKeypad;
	Buzzer _buzzer;
	SevSegms _sevSegms;
	StepperMotor* _dividerMotor;
	DcMotor* _tableMotor;
	Endstop* _dividerEndstop;
	Endstop* _tableEndstop;
	Relay* _relay;

	ElementManager _elementManager;

public:
	Program();
	~Program();

	void init();
	void step();
};

#endif
