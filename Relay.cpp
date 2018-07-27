#include "Relay.h"

Relay::Relay()
{
	pinMode(_pinPull, OUTPUT);
	pinMode(_pinPush, OUTPUT);
}

void Relay::pull()
{
	//to be sure that the opposite is not power on
	digitalWrite(_pinPush, LOW);

	digitalWrite(_pinPull, HIGH);
	delay(250);
	digitalWrite(_pinPull, LOW);
}

void Relay::push()
{
	//to be sure that opposite is not power on
	digitalWrite(_pinPull, LOW);

	digitalWrite(_pinPush, HIGH);
	delay(250);
	digitalWrite(_pinPush, LOW);
}

bool Relay::home()
{
	if (_currentHomeValue < _homedValue)
	{
		//to be sure that opposite is not power on
		digitalWrite(_pinPush, LOW);

		digitalWrite(_pinPull, HIGH);
		delay(1);
		digitalWrite(_pinPull, LOW);

		_currentHomeValue++;

		return false;
	}
	else
	{
		_currentHomeValue = _notHomedValue;

		return true;
	}
}