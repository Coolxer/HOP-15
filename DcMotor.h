#pragma once

#include <Arduino.h>
#include "ProgramState.h"

class Endstop;
class Potentiometer;

class DcMotor
{
private:
	byte _pwmPin = 4; 
	byte _dirPinA = 5;
	byte _dirPinB = 6;
	byte _enablePin = 7;

	byte _speed = 100; //max speed 255

	Endstop* _endstop;
	Potentiometer* _potentiometer;

public:
	DcMotor(Endstop* endstop, Potentiometer* potentiometer);
	~DcMotor();

	void setSpeed();
	byte getSpeed() { return _speed; };

	void enable(bool e);
	void home();
	void move(int steps);

	void moveLeft();
	void moveRight();

};

