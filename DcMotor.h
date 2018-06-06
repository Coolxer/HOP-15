#pragma once

#include <Arduino.h>
#include "ProgramElement.h"

class DcMotor
{
private:
	byte _pwmPin = 4;
	byte _dirPinA = 5;
	byte _dirPinB = 6;

	byte _speed = 100; //max speed 255

	Endstop* _endstop;

public:
	DcMotor(Endstop* endstop);
	~DcMotor();

	void setSpeed(byte speed);
	byte getSpeed() { return _speed; };

	void home();
	void moveLeft();
	void moveRight();

	void manage(ProgramElement* programElement);
};

