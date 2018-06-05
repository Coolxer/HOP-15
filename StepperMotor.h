#ifndef motor_h
#define motor_h

#include <Arduino.h>
#include <Stepper.h>
#include "ProgramElement.h"

class Endstop;

class StepperMotor
{
private:
	byte _motorSteps = 800;
	byte _speed = 100;
	byte _microSteps = 1;

	byte _dirPin;
	byte _stepPin;
	byte _enablePin;

	float _stepsLeft;

	Stepper* _stepper;
	Endstop* _defaultEndstop;

	bool _isEnable;

public:
	StepperMotor(byte dirPin, byte stepPin, byte enablePin);
	StepperMotor(byte dirPin, byte stepPin, byte enablePin, Endstop* defaultEndstop);
	~StepperMotor();

	void setMotorSteps(byte motorSteps);
	void setMotorSpeed(byte speed);
	void setMicroSteps(byte microSteps);

	void enable(bool e);
	
	void home();
	void rotate(int angle);

	void manage(ProgramElement* programElement);
	bool isMoving();

};

#endif
