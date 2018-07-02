#ifndef motor_h
#define motor_h

#include <Arduino.h>
#include <Stepper.h>
#include "ProgramState.h"

class Endstop;

class StepperMotor
{
private:
	byte _motorSteps = 800.0;
	byte _speed = 100.0;
	byte _microSteps = 1;

	byte _dirPin;
	byte _stepPin;
	byte _enablePin;

	Stepper* _stepper;
	Endstop* _endstop;

public:
	StepperMotor(byte dirPin, byte stepPin, byte enablePin, Endstop* endstop);
	~StepperMotor();

	void enable(bool e);
	
	void home();
	void rotate(int angle);

	//void manage(ProgramState* ProgramState);
};

#endif
