#pragma once

#include <Arduino.h>

class Potentiometer
{
private:
	byte _pin = 38; //analog pin
	byte _value; //for motor speed the max value is 255 so i divide it by 4, because the potentiometer value is 0 - 1025
public:
	Potentiometer() {};
	byte getValue() { return _value; };
	void setValue() { _value = analogRead(_pin) / 4; };
};

