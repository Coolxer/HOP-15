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
	byte _speed = 100;
	byte _microSteps = 16;
	int _sumOfSteps = _motorSteps * _microSteps;

	byte _dirPin = 6;
	byte _stepPin = 3;
	byte _enablePin = 8;

	Stepper _stepper = Stepper(_motorSteps, _dirPin, _stepPin);
	Endstop* _endstop;

public:
	StepperMotor(Endstop* endstop);

	void enable(bool e);
	
	void home();
	void rotate(float angle);
};

#endif
