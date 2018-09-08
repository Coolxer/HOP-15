#include "RotaryEncoder.h"

#include "MenuState.h"
#include "Program.h"
#include "DeviceManager.h"
#include "SimpleKeypad.h"

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
		_changeAmount = 1.0;
		break;
	case QUICKLY_MOVE:
		_changeAmount = 200.0;
		break;
	case SPEED_CHANGE:
		_changeAmount = 5.0;
		break;
	case CUTTER_ANGLE_CHANGE:
		_changeAmount = 0.1;
	}
}

short RotaryEncoder::read()
{
	_encA = digitalRead(_pinA);
	_encB = digitalRead(_pinB);

	if ((!_encA) && (_lastA))
	{
		if (_encB)
		{
			_lastA = _encA;
			return _changeAmount;
		}	
		else
		{
			_lastA = _encA;
			return _changeAmount * -1.0;
		}		
	}

	_lastA = _encA;
	return 0;
}

void RotaryEncoder::reset()
{
	_start = true;
	_encA = false;
	_encB = false;
	_lastA = false;

	_currentTime = 0;
	_lastTime = 0;
}