#include "Relay.h"

Relay::Relay()
{
	pinMode(_pinPull, OUTPUT);
	pinMode(_pinPush, OUTPUT);

	digitalWrite(_pinPush, LOW);
	digitalWrite(_pinPull, LOW);
}

void Relay::pull()
{
	digitalWrite(_pinPull, HIGH);
	delay(250);
	digitalWrite(_pinPull, LOW);
}

void Relay::push()
{
	digitalWrite(_pinPush, HIGH);
	delay(150);
	digitalWrite(_pinPush, LOW);
}

bool Relay::home()
{
	if (_currentHomeValue < _homedValue)
	{
		digitalWrite(_pinPush, HIGH);
		delay(1);
		digitalWrite(_pinPush, LOW);

		_currentHomeValue++;

		return false;
	}
	else
	{
		_currentHomeValue = _notHomedValue;

		return true;
	}
}