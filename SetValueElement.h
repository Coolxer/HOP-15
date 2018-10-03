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

	double _minValue;
	double _maxValue;
	double _currentValue;
	double _stepValue;

public:
	SetValueElement() {};
	SetValueElement(char* name, MenuState* state, double minValue, double maxValue, double currentValue, double stepValue);
	~SetValueElement() {};

	virtual void react();

	void increase();
	void decrease();

	float getValue() { return _currentValue; };
	String getValueStr() { return String(_currentValue); }
};

#endif

