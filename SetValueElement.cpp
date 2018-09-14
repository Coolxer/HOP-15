#include "SetValueElement.h"

#include "MenuState.h"
#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"

SetValueElement::SetValueElement(char* name, MenuState* state, float minValue, float maxValue, float currentValue, float stepValue) : Element(name)
{
	_state = state;

	DeviceManager* deviceManager = state->getProgram()->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_rotaryEncoder = deviceManager->requestRotaryEncoder();

	_minValue = minValue;
	_maxValue = maxValue;
	_currentValue = currentValue;
	_stepValue = stepValue;
}

void SetValueElement::react()
{
	char key = _simpleKeypad->getPressedKey();

	float value = _rotaryEncoder->read();

	if (key == KEY_UP || value > 0)
		increase();
	else if (key == KEY_DOWN || value < 0)
		decrease();
	else if (key == KEY_ENTER)
		_state->back();
}

void SetValueElement::increase()
{
	_currentValue += _stepValue;

	if (_currentValue > _maxValue)
		_currentValue = _maxValue;

	_state->needRedraw();
}

void SetValueElement::decrease()
{
	_currentValue -= _stepValue;

	if (_currentValue < _minValue)
		_currentValue = _minValue;

	_state->needRedraw();
}