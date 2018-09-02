#include "StepperMotor.h"
#include "Endstop.h"

StepperMotor::StepperMotor(byte motorSteps, byte dirPin, byte stepPin, byte enablePin)
{
	_motorSteps = motorSteps;
	_dirPin = dirPin;
	_stepPin = stepPin;
	_enablePin = enablePin;

	init();
}

StepperMotor::StepperMotor(byte motorSteps, byte dirPin, byte stepPin, byte enablePin, Endstop* forwardEndstop, Endstop* backwardEndstop)
{
	_motorSteps = motorSteps;
	_dirPin = dirPin;
	_stepPin = stepPin;
	_enablePin = enablePin;

	_forwardEndstop = forwardEndstop;
	_backwardEndstop = backwardEndstop;

	init();
}


void StepperMotor::init() 
{
	_stepper = &A4988(_motorSteps, _dirPin, _stepPin, _enablePin);

	_stepper->begin(_speed, _microSteps);
	disable();
}

void StepperMotor::enable()
{
	_stepper->enable();
}

void StepperMotor::disable()
{
	_stepper->disable();
}

void StepperMotor::rotate(long angle)
{
	_stepper->rotate(-angle);
}

void StepperMotor::setSpeed(byte speed)
{
	_speed = speed;
	_stepper->setRPM(_speed);
}

bool StepperMotor::home()
{
	if (_forwardEndstop->isClicked())
	{
		return true;
	}
	else
	{
		_stepper->move(-1);
		return false;
	}
}

void StepperMotor::move(long steps)
{
	_stepper->move(steps);
}

bool StepperMotor::isEnable()
{
	if (digitalRead(_enablePin) == HIGH)
		return true;
	else
		return false;
}