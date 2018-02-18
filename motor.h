#ifndef motor_h
#define motor_h

#include <Arduino.h>
#include <Stepper.h>
#include "ProgramElement.h"

class Motor
{
private:
	byte _motorSteps = 200;
	byte _speed = 120;
	byte _microSteps = 1;

	byte _dirPin; //6
	byte _stepPin; //3
	byte _enablePin; //8

	float _stepsLeft;

	Stepper* _stepper;

	bool _isEnable;

public:
	Motor(byte dirPin, byte stepPin, byte enablePin);
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
