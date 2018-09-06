#pragma once

#include <Arduino.h>

class MenuState;
class SimpleKeypad;

class RotaryEncoder
{
private:
	//define pins A and B for rotary encoder
	byte _pinA = 51;
	byte _pinB = 53;

	//current reading value from encoder
	//int _reading = 0;

	//the smallest value that can be get by encoder
	//short _lowest = -1000;

	//the highest value that can be get by encoder
	//short _highest = 1000;

	//the step size, that defines how much the value will change (increase/decrease) with each pulse
	short _changeAmount = 1;

	//bools variables store the current state of encoder( it allows to find in which direction the encoder is rotated reacts accordingly 
	bool _encA = false;
	bool _encB = false;

	//store true if the last signal was from A pin 
	bool _lastA = false;

	// Timing for polling the encoder
	unsigned long _currentTime = 0;
	unsigned long _lastTime = 0;

	MenuState* _state;
	SimpleKeypad* _simpleKeypad;

public:
	RotaryEncoder();

	void init(MenuState* state);

	enum OperationType { SLOWLY_MOVE, QUICKLY_MOVE, SPEED_CHANGE };

	void setOperationType(OperationType operationType);
	short getValue();

	//int getReading() { return _reading; };

	short getChangeAmount() { return _changeAmount; };
	void setChangeAmount(short changeAmount) { _changeAmount = changeAmount; };
};