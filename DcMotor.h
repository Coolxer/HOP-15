#pragma once

#include <Arduino.h>
#include "ProgramState.h"

class Endstop;
class Potentiometer;

class DcMotor
{
private:
	byte _pwmPin = 17; 
	byte _dirPinA = 18;
	byte _dirPinB = 19;
	byte _enablePin = 20;

	byte _speed; //max speed 255

	Endstop* _endstop;
	Potentiometer* _potentiometer;

public:
	DcMotor(Endstop* endstop, Potentiometer* potentiometer);

	void setSpeed();
	byte getSpeed() { return _speed; };

	void enable(bool e);
	void home();

	void moveBackward();
	void moveForward();
	void stop();

};

