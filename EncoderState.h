#ifndef _ENCODERSTATE_h
#define _ENCODERSTATE_h

#include <Arduino.h>
#include "State.h"

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;
class RotaryEncoder;
class AccelStepper;

class Endstop;

enum Operations
{
	MOVE_DIVIDER_MOTOR,
	MOVE_TABLE_MOTOR,
	//CHANGE_SPEED,
	//CHANGE_CUTTER_ANGLE
};

class EncoderState : public State
{
private:
	Lcd * _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	RotaryEncoder* _rotaryEncoder;

	AccelStepper* _dividerMotor;
	AccelStepper* _tableMotor;

	Endstop* _forwardTableEndstop;
	Endstop* _backwardTableEndstop;

	int _position = 0;

	short _reading;

	Operations _operation;

public:
	virtual void init();
	virtual void react();
	virtual void reset();

	void setOperation(Operations operation) { _operation = operation; };
	Operations getOperation() { return _operation; };

	int getPosition() { return _position; };
};

#endif