#pragma once
#include <Arduino.h>

class Relay
{
private:
	byte _pinPull = 49;
	byte _pinPush = 51;

	int _notHomedValue = 0;
	int _homedValue = 250;
	int _currentHomeValue = 0;

public:
	Relay();
	void pull();
	void push();
	bool home();
};
