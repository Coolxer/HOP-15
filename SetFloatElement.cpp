#include "SetFloatElement.h"

SetFloatElement::SetFloatElement(char* name, MenuState* state, float minValue, float maxValue, float currentValue, float stepValue):SetValueElement(state)
{
	_minValue = minValue;
	_maxValue = maxValue;
	_currentValue = currentValue;
	_stepValue = stepValue;
}

void SetFloatElement::increase()
{
	_currentValue += _stepValue;

	if (_currentValue > _maxValue)
		_currentValue = _maxValue;

	_state->needRedraw();
}

void SetFloatElement::decrease()
{
	_currentValue -= _stepValue;

	if (_currentValue < _minValue)
		_currentValue = _minValue;

	_state->needRedraw();
}
