#include "StepperMotor.h"
#include "Endstop.h"

StepperMotor::StepperMotor(Endstop* endstop)
{
	_endstop = endstop;

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

void StepperMotor::home()
{
	if (_endstop != nullptr)
	{
		while (!_endstop->isClicked())
			rotate(-5);
	}
}

void StepperMotor::rotate(float angle)
{
	int stepsToRotate = int(((float)angle * _sumOfSteps) / 360.0);

	_stepper.step(stepsToRotate);
}