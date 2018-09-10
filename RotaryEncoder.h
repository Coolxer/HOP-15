#pragma once

#include <Arduino.h>

class RotaryEncoder
{
private:
	//define pins A and B for rotary encoder
	byte _pinA = 51;
	byte _pinB = 53;

	//bools variables store the current state of encoder( it allows to find in which direction the encoder is rotated reacts accordingly 
	bool _encA = false;
	bool _encB = false;

	//store true if the last signal was from A pin 
	bool _lastA = false;

	bool _start = true;

	float _changeAmount = 1.0;

public:
	RotaryEncoder();

	enum OperationType { SLOWLY_MOVE, QUICKLY_MOVE, SPEED_CHANGE, CUTTER_ANGLE_CHANGE };

	void setOperationType(OperationType operationType);
	float read();

	void reset();

	short getChangeAmount() { return _changeAmount; };
	void setChangeAmount(short changeAmount) { _changeAmount = changeAmount; };
};