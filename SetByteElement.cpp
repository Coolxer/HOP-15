#include "SetByteElement.h"

SetByteElement::SetByteElement(char* name, MenuState* state, byte minValue, byte maxValue, byte currentValue, byte stepValue):SetValueElement(state)
{
	_minValue = minValue;
	_maxValue = maxValue;
	_currentValue = currentValue;
	_stepValue = stepValue;
}

void SetByteElement::increase()
{
	_currentValue += _stepValue;

	if (_currentValue > _maxValue)
		_currentValue = _maxValue;

	_state->needRedraw();
}

void SetByteElement::decrease()
{
	_currentValue -= _stepValue;

	if (_currentValue < _minValue)
		_currentValue = _minValue;

	_state->needRedraw();
}