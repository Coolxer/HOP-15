#include "SetValueElement.h"

SetValueElement::SetValueElement(char* name,
								 Lcd* lcd, SimpleKeypad* simpleKeypad,
								 char* valueName, byte minValue, byte maxValue, byte currentValue, byte stepValue)
{
	_lcd = lcd;
	_simpleKeypad = simpleKeypad;

	_valueName = valueName;
	_minValue = minValue;
	_maxValue = maxValue;
	_currentValue = currentValue;
	_stepValue = stepValue;
}

void SetValueElement::react()
{
	if (_lcd != nullptr && _simpleKeypad != nullptr)
	{
		if (!_inited)
		{

		}
		else if (_simpleKeypad->getPressedKey() == KEY_UP)
		{
			_currentValue += _stepValue;

			if (_currentValue > _maxValue)
				_currentValue = _maxValue;
		}
		else if (_simpleKeypad->getPressedKey() == KEY_DOWN)
		{
			_currentValue -= _stepValue;

			if (_currentValue < _minValue)
				_currentValue = _minValue;
		}
	}
}

