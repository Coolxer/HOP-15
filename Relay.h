#pragma once
#include <Arduino.h>

class Relay
{
private:
	byte _pin = 21;
public:
	Relay();
	void setHighState(bool high);
};

