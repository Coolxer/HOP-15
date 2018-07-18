#include "DcMotor.h"

#include "Endstop.h"
#include "Potentiometer.h"

DcMotor::DcMotor(Endstop* endstop, Potentiometer* potentiometer)
{
	_endstop = endstop;
	_potentiometer = potentiometer;
	
	pinMode(_pwmPin, OUTPUT);
	pinMode(_dirPinA, OUTPUT);
	pinMode(_dirPinB, OUTPUT);
	pinMode(_enablePin, OUTPUT);

	enable(false);
}

DcMotor::~DcMotor()
{
	delete _endstop;
	delete _potentiometer;
}

void DcMotor::setSpeed()
{
	_potentiometer->setValue();
	_speed = _potentiometer->getValue();
	
	analogWrite(_pwmPin, _speed);
}

void DcMotor::enable(bool e)
{
	if (e)
		digitalWrite(_enablePin, HIGH);
	else
	{
		stop();
		digitalWrite(_enablePin, LOW);
	}
}

void DcMotor::home()
{
	if (_endstop != nullptr)
	{
		while (!_endstop->isClicked())
			moveBackward();
		stop();
	}
}

void DcMotor::moveBackward()
{
	digitalWrite(_dirPinA, HIGH);
	digitalWrite(_dirPinB, LOW);
}

void DcMotor::moveForward()
{
	digitalWrite(_dirPinA, LOW);
	digitalWrite(_dirPinB, HIGH);
}

void DcMotor::stop()
{
	digitalWrite(_dirPinA, LOW);
	digitalWrite(_dirPinB, LOW);
	_speed = 0;
	analogWrite(_pwmPin, _speed);

}
