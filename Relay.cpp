#include "Relay.h"

Relay::Relay()
{
	pinMode(_pin, OUTPUT);
}

void Relay::setHighState(bool state)
{
	if (state)
		digitalWrite(_pin, HIGH);
	else
		digitalWrite(_pin, LOW);
}

bool Relay::isHighState()
{
	if (digitalRead(_pin) == HIGH)
		return true;
	else
		return false;
}

