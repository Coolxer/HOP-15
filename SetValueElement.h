#ifndef _SETVALUEELEMENT_h
#define _SETVALUEELEMENT_h

#include <Arduino.h>
#include "Element.h"

class Lcd;
class SimpleKeypad;

class SetValueElement: public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;

	byte _minValue;
	byte _maxValue;
	byte _currentValue;
	byte _stepValue;

public:
	SetValueElement(char* name,
					Lcd* lcd, SimpleKeypad* simpleKeypad,
					byte minValue, byte maxValue, byte currentValue, byte stepValue);
	~SetValueElement() {};

	virtual void react();

	void increase();
	void decrease();

	byte getValue() { return _currentValue; };
	String getValueStr() { return String(_currentValue); };
	
};

#endif

