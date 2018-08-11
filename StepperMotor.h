#ifndef motor_h
#define motor_h

#include <Arduino.h>

#include "A4988.h"

class Endstop;

class StepperMotor
{
private:
	int _motorSteps = 200;
	byte _speed = 60; // range 1 - 200
	byte _microSteps = 8;

	byte _dirPin = 6;
	byte _stepPin = 3;
	byte _enablePin = 8;

	A4988 _stepper = A4988(_motorSteps, _dirPin, _stepPin, _enablePin);

public:
	StepperMotor();

	void enable(); //turns on the motor so it can move
	void disable(); // turns off the motor makes that you can move it by hand <I>

	void move(long steps);
	void rotate(long angle);

	void setSpeed(byte speed);
	bool home(Endstop* endstop);

	bool isEnable();

};

#endif
