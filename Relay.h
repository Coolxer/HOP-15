#pragma once
#include <Arduino.h>

class Relay
{
private:
	byte _pinPull = 49;
	byte _pinPush = 51;
public:
	Relay();
	void pull();
	void push();
};

