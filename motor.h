#ifndef motor_h
#define motor_h

#include <Arduino.h>
#include <Stepper.h>
#include "ProgramElement.h"

class Endstop;

class Motor
{
private:
	byte _motorSteps = 200;
	byte _speed = 120;
	byte _microSteps = 1;

	byte _dirPin;
	byte _stepPin;
	byte _enablePin;

	float _stepsLeft;

	Stepper* _stepper;
	Endstop* _defaultEndstop;

	bool _isEnable;

public:
	Motor(byte dirPin, byte stepPin, byte enablePin);
	Motor(byte dirPin, byte stepPin, byte enablePin, Endstop* defaultEndstop);
	~Motor();

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
