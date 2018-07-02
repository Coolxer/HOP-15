#pragma once

#include <Arduino.h>
#include "ProgramState.h"
#include "Potentiometer.h"

class DcMotor
{
private:
	byte _pwmPin = 4; 
	byte _dirPinA = 5;
	byte _dirPinB = 6;

	byte _speed = 100; //max speed 255

	Endstop* _endstop;
	Potentiometer* _potentiometer;

public:
	DcMotor(Endstop* endstop);
	~DcMotor();

	void setSpeed();
	byte getSpeed() { return _speed; };

	void home();
	void move(byte );

	void moveLeft();
	void moveRight();

};

