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
	//delay(3000);
}

void DcMotor::moveRight()
{
	digitalWrite(_dirPinB, HIGH);
	digitalWrite(_dirPinA, LOW);
	//delay(3000);
}

void DcMotor::manage(ProgramElement* programElement)
{

}
