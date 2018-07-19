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

	//Max speed 255
	byte _speed;

	//Time motor will move until stop in ms
	int _moveTime = 10;

	Endstop* _endstop;
	Potentiometer* _potentiometer;

public:
	DcMotor(Endstop* endstop, Potentiometer* potentiometer);

	void setSpeed();
	byte getSpeed() { return _speed; };

	void enable(bool e);
	bool home();

	void moveBackward();
	void moveForward();
	void stop();

};

