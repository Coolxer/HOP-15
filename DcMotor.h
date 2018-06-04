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

public:
	DcMotor();
	~DcMotor();

	void setSpeed(byte speed);
	byte getSpeed() { return _speed; };

	void moveLeft();
	void moveRight();

	void manage(ProgramElement* programElement);
};

