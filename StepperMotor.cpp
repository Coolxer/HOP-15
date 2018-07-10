#include "StepperMotor.h"
#include "Endstop.h"

StepperMotor::StepperMotor(byte dirPin, byte stepPin, byte enablePin, Endstop* endstop)
{
	_dirPin = dirPin;
	_stepPin = stepPin;
	_enablePin = enablePin;

	_endstop = endstop;

	_stepper = new Stepper(_motorSteps, _dirPin, _stepPin);
	_stepper->setSpeed(_speed);

	pinMode(_enablePin, OUTPUT);
	enable(true);
}

StepperMotor::~StepperMotor()
{
	delete _stepper;
	delete _endstop;
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

void StepperMotor::rotate(int angle)
{
	float stepsToRotate = angle * _motorSteps * _microSteps / 360;

	_stepper->step(stepsToRotate);
}