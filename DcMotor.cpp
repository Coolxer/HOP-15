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

void DcMotor::home()
{
	if (_endstop != nullptr)
	{
		while (!_endstop->isClicked())
			moveLeft();
	}
}

void DcMotor::move(int steps)
{
	if (steps < 0)
		moveLeft();
	else
		moveRight();
}

void DcMotor::moveLeft()
{
	digitalWrite(_dirPinA, HIGH);
	digitalWrite(_dirPinB, LOW);
}

void DcMotor::moveRight()
{
	digitalWrite(_dirPinA, LOW);
	digitalWrite(_dirPinB, HIGH);
}

