#pragma once
#include <Arduino.h>
#include "SetValueElement.h"

class SetByteElement : public SetValueElement
{
private:
	byte _minValue;
	byte _maxValue;
	byte _currentValue;
	byte _stepValue;

public:
	SetByteElement(char* name, MenuState* state, byte minValue, byte maxValue, byte currentValue, byte stepValue);

	void increase();
	void decrease();
};

