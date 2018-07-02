#pragma once

#include <Arduino.h>

class Potentiometer
{
private:
	byte _pin = 38; //analog pin
	byte _value;
public:
	Potentiometer() {};
	byte getValue() { return _value; };
	void setValue() { _value = analogRead(_pin); };
};

