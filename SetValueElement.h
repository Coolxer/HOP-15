#ifndef _SETVALUEELEMENT_h
#define _SETVALUEELEMENT_h

#include <Arduino.h>
#include "Element.h"

class MenuState;

class Lcd;
class SimpleKeypad;
class RotaryEncoder;

class SetValueElement: public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	RotaryEncoder* _rotaryEncoder;

public:
	SetValueElement() {};
	SetValueElement(MenuState* state);

	virtual void react();

	virtual void increase();
	virtual void decrease();

	virtual String getValueStr();
};

#endif

