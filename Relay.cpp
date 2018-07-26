#include "Relay.h"

Relay::Relay()
{
	pinMode(_pin, OUTPUT);
	setHighState(false);
}

void Relay::setHighState(bool high)
{
	if (high)
		digitalWrite(_pin, HIGH);
	else
		digitalWrite(_pin, LOW);
}

