#ifndef motor_h
#define motor_h

#include <Arduino.h>

#include "A4988.h"

class Endstop;

class StepperMotor
{
private:
	int _motorSteps;
	byte _speed = 60; // range 1 - 200
	byte _microSteps = 8;

	byte _dirPin;
	byte _stepPin;
	byte _enablePin;

	A4988 _stepper;

	Endstop* _forwardEndstop;
	Endstop* _backwardEndstop;

	void init();

public:
	StepperMotor(int motorSteps, byte dirPin, byte stepPin, byte enablePin);
	StepperMotor(int motorSteps, byte dirPin, byte stepPin, byte enablePin, Endstop* forwardEndstop, Endstop* backwardEndstop);

	void enable(); //turns on the motor so it can move
	void disable(); // turns off the motor makes that you can move it by hand <I>

	void move(long steps);
	void rotate(long angle);

	void setSpeed(byte speed);
	bool home();

	bool isEnable();

};

#endif
