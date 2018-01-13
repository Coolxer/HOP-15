#include "SetValueElement.h"

SetValueElement::SetValueElement(char* name,
								 Lcd* lcd, SimpleKeypad* simpleKeypad,
								 byte minValue, byte maxValue, byte currentValue, byte stepValue)
{
	_lcd = lcd;
	_simpleKeypad = simpleKeypad;

	_minValue = minValue;
	_maxValue = maxValue;
	_currentValue = currentValue;
	_stepValue = stepValue;
}

void SetValueElement::react()
{
	if (_lcd != nullptr && _simpleKeypad != nullptr)
	{
		_simpleKeypad->manage(this);

		if (_needRedraw)
		{
			_lcd->manage(this);
			_needRedraw = false;
		}
	}
}

void SetValueElement::increase()
{
	_currentValue += _stepValue;

	if (_currentValue > _maxValue)
		_currentValue = _maxValue;
}

void SetValueElement::decrease()
{
	_currentValue -= _stepValue;

	if (_currentValue < _minValue)
		_currentValue = _minValue;
}
