#include "Encoder.h"

Encoder::Encoder()
{
	digitalWrite(_pinA, INPUT_PULLUP);
	digitalWrite(_pinB, INPUT_PULLUP);
}

void Encoder::run() 
{
	_currentTime = millis();
	_lastTime = _currentTime;

	if (_currentTime >= _lastTime + 5)
	{
		_encA = digitalRead(_pinA);
		_encB = digitalRead(_pinB);

		if ((!_encA) && (_lastA))
		{
			if (_encB)
				_reading--;
			else
				_reading++;
		}
		_lastA = _encA;
		_lastTime = _currentTime;
	}
}
