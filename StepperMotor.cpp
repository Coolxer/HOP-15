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