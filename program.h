#ifndef program_h
#define program_h

#include "input.h"
#include "output.h"
#include "ElementManager.h"
#include "TestElement.h"
#include "simpleKeypad.h"
#include "lcd.h"
#include "buzzer.h"
#include "motor.h"

class Program
{
private:
	Lcd lcd;
	SimpleKeypad simpleKeypad;
	Buzzer buzzer;
	Motor motor;

	ElementManager elementManager;

public:
	Program();
	~Program();

	void init();
	void step();
};

#endif
