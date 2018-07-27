#pragma once
#include <Arduino.h>

class Relay
{
private:
	byte _pinPull = 49;
	byte _pinPush = 51;

	bool isHomed = false;
public:
	Relay();
	void pull();
	void push();
	void home();
};