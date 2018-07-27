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
	delay(200);
	digitalWrite(_pinPull, LOW);
}

void Relay::home()
{
	if (!isHomed)
	{
		digitalWrite(_pinPull, HIGH);
		delay(500);
		digitalWrite(_pinPull, LOW);
		isHomed = true;
	}
}

void Relay::push()
{
	digitalWrite(_pinPush, HIGH);
	delay(100);
	digitalWrite(_pinPush, LOW);
}