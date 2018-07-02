#include "DcMotor.h"
#include "Endstop.h"

DcMotor::DcMotor(Endstop* endstop)
{
	_endstop = endstop;
	_potentiometer = new Potentiometer();
	
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
	_speed = _potentiometer->getValue() / 4;
	
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

void DcMotor::move()

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

