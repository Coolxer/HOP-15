#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder()
{
	digitalWrite(_pinA, INPUT_PULLUP);
	digitalWrite(_pinB, INPUT_PULLUP);
}

void RotaryEncoder::setOperationType(OperationType operationType)
{
	switch (operationType)
	{
	case SLOWLY_MOVE:
		_changeAmount = 1;
		break;
	case QUICKLY_MOVE:
		_changeAmount = 200;
		break;
	case SPEED_CHANGE:
		_changeAmount = 5;
		break;
	}
}

short RotaryEncoder::getValue()
{
	/*
	_currentTime = millis();
	_lastTime = _currentTime;
	if (_currentTime >= _lastTime + 5)
	{
	_encA = digitalRead(_pinA);
	_encB = digitalRead(_pinB);
	if ((!_encA) && (_lastA))
	{
	if (_encB)
	return _changeAmount;
	else
	return _changeAmount * -1;
	}
	_lastA = _encA;
	_lastTime = _currentTime;
	}
	*/

	if ((!_encA) && (_lastA))
	{
		if (_encB)
			return _changeAmount;
		else
			return _changeAmount * (-1);
	}

	_lastA = _encA;
}