#include "StepperMotor.h"
#include "Endstop.h"

StepperMotor::StepperMotor()
{
	_stepper.begin(_speed, _microSteps);
	disable();
}

void StepperMotor::enable()
{
	_stepper.enable();
}

void StepperMotor::disable()
{
	_stepper.disable();
}

void StepperMotor::rotate(long angle)
{
	_stepper.rotate(-angle);
}

void StepperMotor::setSpeed(byte speed)
{
	_speed = speed;
	_stepper.setRPM(_speed);
}

bool StepperMotor::home(Endstop* endstop)
{
	if (endstop->isClicked())
	{
		return true;
	}
	else
	{
		_stepper.move(-1);
		return false;
	}
}

void StepperMotor::move(long steps)
{
	_stepper.move(steps);
}

bool StepperMotor::isEnable()
{
	if (digitalRead(_enablePin) == HIGH)
		return true;
	else
		return false;
}