#ifndef _ManualControlState_h
#define _ManualControlState_h

#include <Arduino.h>
#include "State.h"

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;
class RotaryEncoder;
class AccelStepper;

class Endstop;

class ManualControlState : public State
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
	float _reading;
	unsigned int _value = 1;

	String _operation;
	char _lastKeyPressed = ' ';

public:
	virtual void init();
	virtual void react();
	virtual void reset();

	void setOperation(String operation) { _operation = operation; };
	String getOperation() { return _operation; };
	int getPosition() { return _position; };
};

#endif