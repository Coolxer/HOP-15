#pragma once
#include <Arduino.h>

class Relay
{
private:
	byte _pin = 53;
public:
	Relay();
	void setHighState(bool high);
};

