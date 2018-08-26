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
	byte _speed = 255;

	Endstop* _forwardEndstop;
	Endstop* _backwardEndstop;
	Potentiometer* _potentiometer;

public:
	DcMotor(Endstop* forwardEndstop, Endstop* backwardEndstop, Potentiometer* potentiometer);

	void setSpeed();
	byte getSpeed() { return _speed; };

	void enable(); //it's turns the motor on and able its to move
	void disable(); //turns off the motor
	bool isEnable();

	bool home();

	void moveBackward(int moveTime);
	void moveForward(int moveTime);
	void stop();

};

