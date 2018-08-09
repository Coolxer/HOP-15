#ifndef motor_h
#define motor_h

#include <Arduino.h>
#include <Stepper.h>
#include "ProgramState.h"

class Endstop;

class StepperMotor
{
private:
	int _motorSteps = 800;
	byte _speed = 200;
	byte _microSteps = 8;
	float _sumOfSteps = _motorSteps * _microSteps * 2.0967741;

	byte _dirPin = 6;
	byte _stepPin = 3;
	byte _enablePin = 8;

	Stepper _stepper = Stepper(_motorSteps, _dirPin, _stepPin);

public:
	StepperMotor();

	void enable(bool e);
	void rotate(float angle);
	void setSpeed(byte speed);
	bool home(Endstop* endstop);
};

#endif
