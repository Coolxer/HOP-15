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

short RotaryEncoder::read()
{
	_encA = digitalRead(_pinA);
	_encB = digitalRead(_pinB);

	if ((!_encA) && (_lastA))
	{
		if (_encB)
		{
			_lastA = _encA;
			return -1;
		}	
		else
		{
			_lastA = _encA;
			return 1;
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
}