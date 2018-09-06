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
	_readA = digitalRead(_pinA);

	if ((_lastA == LOW) && (_readA == HIGH))
	{
		if (digitalRead(_pinB) == LOW)
			return _changeAmount;
		else
			return _changeAmount * -1.0;
	}

	_lastA = _readA;

	return 0;
}