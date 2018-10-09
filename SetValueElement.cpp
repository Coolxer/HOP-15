#include "SetValueElement.h"

#include "MenuState.h"
#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"

SetValueElement::SetValueElement(char* name, MenuState* state, double minValue, double maxValue, double currentValue, double stepValue) : Element(name)
{
	_state = state;

	DeviceManager* deviceManager = state->getProgram()->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
	_rotaryEncoder = deviceManager->requestRotaryEncoder();

	_minValue = minValue;
	_maxValue = maxValue;
	_currentValue = currentValue;
	_stepValue = stepValue;
}

void SetValueElement::react()
{
	char key = _simpleKeypad->getPressedKey();

	short value = _rotaryEncoder->read();

	if (key == KEY_UP || value == 1)
		increase();
	else if (key == KEY_DOWN || value == -1)
		decrease();
	else if (key == KEY_ENTER)
	{
		_buzzer->playOnPress();
		_state->back();
	}
		
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