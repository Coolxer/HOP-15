#include "SetValueElement.h"

#include "MenuState.h"
#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"

SetValueElement::SetValueElement(MenuState* state)
{
	_state = state;

	DeviceManager* deviceManager = state->getProgram()->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_rotaryEncoder = deviceManager->requestRotaryEncoder();
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
