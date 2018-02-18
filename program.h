#ifndef program_h
#define program_h

#include "input.h"
#include "output.h"
#include "ElementManager.h"
#include "simpleKeypad.h"
#include "lcd.h"
#include "sevSegms.h"
#include "buzzer.h"
#include "motor.h"
#include "MenuElement.h"
#include "IntroductionElement.h"
#include "ProgramElement.h"
#include "endstop.h"

#include <Stepper.h>

class Program
{
private:
	Lcd _lcd;
	SimpleKeypad _simpleKeypad;
	Buzzer _buzzer;
	SevSegms _sevSegms;
	Motor* _dividerMotor;
	Motor* _tableMotor;
	Endstop* _dividerEndstop;
	Endstop* _tableEndstop;

	ElementManager _elementManager;

public:
	Program();
	~Program();

	void init();
	void step();
};

#endif
