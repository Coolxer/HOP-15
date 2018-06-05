#pragma once
#include <Arduino.h>

class Relay
{
private:
	byte _pin;
public:
	Relay();
	void setHighState(bool high);
	bool isHighState();
};

