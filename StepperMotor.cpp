#include "StepperMotor.h"
#include "Endstop.h"

StepperMotor::StepperMotor(byte dirPin, byte stepPin, byte enablePin)
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

StepperMotor::StepperMotor(byte dirPin, byte stepPin, byte enablePin, Endstop* defaultEndstop)
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

StepperMotor::~StepperMotor()
{
	delete _stepper;
}

void StepperMotor::setMotorSteps(byte motorSteps)
{
	_motorSteps = motorSteps;
}

void StepperMotor::setMotorSpeed(byte speed)
{
	_speed = speed;
	_stepper->setSpeed(_speed);
}

void StepperMotor::setMicroSteps(byte microSteps)
{
	_microSteps = microSteps;
}

void StepperMotor::enable(bool e)
{
	if (e)
		digitalWrite(_enablePin, LOW);
	else
		digitalWrite(_enablePin, HIGH);

	_isEnable = e;
}

void StepperMotor::home()
{
	if (_defaultEndstop != nullptr)
	{
		while (!_defaultEndstop->isClicked())
			rotate(-5);
	}
}

void StepperMotor::rotate(int angle)
{
	float stepsToRotate = angle * _motorSteps * _microSteps / 360;
	_stepsLeft = abs(stepsToRotate);

	_stepper->step(stepsToRotate);
}

bool StepperMotor::isMoving()
{
	if (_stepsLeft > 0)
		return true;
	else
		return false;
}

void StepperMotor::manage(ProgramElement* programElement)
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