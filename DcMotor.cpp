#include "DcMotor.h"
#include "Endstop.h"

DcMotor::DcMotor(Endstop* endstop)
{
	_endstop = endstop;
	
	pinMode(_pwmPin, OUTPUT);
	pinMode(_dirPinA, OUTPUT);
	pinMode(_dirPinB, OUTPUT);
}

DcMotor::~DcMotor()
{
	delete _endstop;
}

void DcMotor::setSpeed(byte speed)
{
	analogWrite(_pwmPin, speed);
	_speed = speed;
}

void DcMotor::home()
{
	if (_endstop != nullptr)
	{
		while (!_endstop->isClicked())
			moveLeft();
	}
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

void DcMotor::manage(ProgramElement* programElement)
{

}
