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

	float _minValue;
	float _maxValue;
	float _currentValue;
	float _stepValue;

public:
	SetValueElement() {};
	SetValueElement(char* name, MenuState* state, float minValue, float maxValue, float currentValue, float stepValue);
	~SetValueElement() {};

	virtual void react();

	void increase();
	void decrease();

	float getValue() { return _currentValue; };
	String getValueStr() { return String(_currentValue); }
};

#endif

