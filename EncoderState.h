#pragma once
#include "State.h"

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;
class RotaryEncoder;
class A4988;

enum Operations
{
	MOVING_DIVIDER_MOTOR,
	MOVING_TABLE_MOTOR,
	CHANGE_SPEED,
	CHANGE_CUTTER_ANGLE
};

class EncoderState : public State
{
private:
	Lcd * _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	RotaryEncoder* _rotaryEncoder;

	A4988* _dividerMotor;
	A4988* _tableMotor;

	float _cutterAngle = 24.0;
	int _position = 0;
	int _speed = 15.0;

	short _reading;

	Operations _operation;

public:
	virtual void init();
	virtual void react();
	virtual void reset();

	void setOperation(Operations operation) { _operation = operation; };
	Operations getOperation() { return _operation; };

	int getPosition() { return _position; };
	int getSpeed() { return _speed; };
	float getCutterAngle() { return _cutterAngle; };
};

