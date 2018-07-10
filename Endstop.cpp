#include "Endstop.h"

Endstop::Endstop(byte pin)
{
	_pin = pin;
	pinMode(_pin, INPUT_PULLUP);
}

bool Endstop::isClicked()
{
	if (digitalRead(_pin) == LOW)
		return true;
	else
		return false;
}