#include "StepperMotor.h"
#include "Endstop.h"

StepperMotor::StepperMotor()
{
	_stepper.setSpeed(_speed);

	pinMode(_enablePin, OUTPUT);
	enable(false);
}

void StepperMotor::enable(bool e)
{
	if (e)
		digitalWrite(_enablePin, LOW);
	else
		digitalWrite(_enablePin, HIGH);
}

void StepperMotor::rotate(float angle)
{
	int stepsToRotate = int(((float)angle * _sumOfSteps) / 360.0);

	_stepper.step(stepsToRotate);
}

void StepperMotor::setSpeed(byte speed)
{
	_speed = speed;
	_stepper.setSpeed(speed);
}