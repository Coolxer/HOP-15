#ifndef _SETVALUEELEMENT_h
#define _SETVALUEELEMENT_h

#include <Arduino.h>
#include "Element.h"

class MenuState;

class Lcd;
class SimpleKeypad;
class Buzzer;
class RotaryEncoder;

class SetValueElement: public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	RotaryEncoder* _rotaryEncoder;

	double _minValue;
	double _maxValue;
	double _currentValue;
	double _stepValue;

	//If user started to input value by pressing number keys
	bool _manualInput = false;
	short _manualKeyValue = -1;

public:
	SetValueElement() {};
	SetValueElement(char* name, MenuState* state, double minValue, double maxValue, double currentValue, double stepValue);
	~SetValueElement() {};

	virtual void react();

	void increase();
	void decrease();
	void validate();

	float getValue() { return _currentValue; };
	String getValueStr() { return String(_currentValue); }
};

#endif

