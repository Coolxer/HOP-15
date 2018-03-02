#include "motor.h"
#include "endstop.h"

Motor::Motor(byte dirPin, byte stepPin, byte enablePin)
{
	_dirPin = dirPin;
	_stepPin = stepPin;
	_enablePin = enablePin;

	_defaultEndstop = nullptr;

	_stepper = new Stepper(_motorSteps, _dirPin, _stepPin);
	_stepper->setSpeed(_speed);

	pinMode(_enablePin, OUTPUT);
	enable(true);
}

Motor::Motor(byte dirPin, byte stepPin, byte enablePin, Endstop* defaultEndstop)
{
	_dirPin = dirPin;
	_stepPin = stepPin;
	_enablePin = enablePin;

	_defaultEndstop = defaultEndstop;

	_stepper = new Stepper(_motorSteps, _dirPin, _stepPin);
	_stepper->setSpeed(_speed);

	pinMode(_enablePin, OUTPUT);
	enable(true);
}

Motor::~Motor()
{
	delete _stepper;
}

void Motor::setMotorSteps(byte motorSteps)
{
	_motorSteps = motorSteps;
}

void Motor::setMotorSpeed(byte speed)
{
	_speed = speed;
	_stepper->setSpeed(_speed);
}

void Motor::setMicroSteps(byte microSteps)
{
	_microSteps = microSteps;
}

void Motor::enable(bool e)
{
	if (e)
		digitalWrite(_enablePin, LOW);
	else
		digitalWrite(_enablePin, HIGH);

	_isEnable = e;
}

void Motor::home()
{
	if (_defaultEndstop != nullptr)
	{
		while (!_defaultEndstop->isClicked())
			rotate(-5);
	}
}

void Motor::rotate(int angle)
{
	float stepsToRotate = angle * _motorSteps * _microSteps / 360;
	_stepsLeft = abs(stepsToRotate);

	_stepper->step(stepsToRotate);
}

bool Motor::isMoving()
{
	if (_stepsLeft > 0)
		return true;
	else
		return false;
}

void Motor::manage(ProgramElement* programElement)
{
	if(programElement->canChangeFeather())
	{
		programElement->setRotatedInCycle(true);

		byte feather = programElement->getCurrentFeather();
		byte feathers = programElement->getFeathersCount();
		byte cycle = programElement->getCurrentCycle();
		byte cycles = programElement->getCyclesCount();
		int rotateAngle = programElement->getRotateAngle();

		//delay(1000);
		rotate(rotateAngle);

		feather++;
		if (feather > feathers)
		{
			feather = 1;
			cycle++;

			if (cycle > cycles)
				programElement->finish();
			else
			{
				programElement->setCurrentFeather(feather);
				programElement->setCurrentCycle(cycle);
			}
		}
		else
			programElement->setCurrentFeather(feather);
	}
}