#pragma once
#include <Arduino.h>
#include "SetValueElement.h"

class MenuState;

class SetFloatElement : public SetValueElement
{
private:
	float _minValue;
	float _maxValue;
	float _currentValue;
	float _stepValue;
public:
	SetFloatElement(char* name, MenuState* state, float minValue, float maxValue, float currentValue, float stepValue);

	void increase();
	void decrease();

	float getValue() { return value; };
	String getValueStr() { return String(_currentValue, 1); };
};

