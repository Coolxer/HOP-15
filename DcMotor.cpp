#include "DcMotor.h"

DcMotor::DcMotor()
{
	pinMode(_pwmPin, OUTPUT);
	pinMode(_dirPinA, OUTPUT);
	pinMode(_dirPinB, OUTPUT);
}

DcMotor::~DcMotor()
{

}

void DcMotor::setSpeed(byte speed)
{
	analogWrite(_pwmPin, speed);
	_speed = speed;
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
