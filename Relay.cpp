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
