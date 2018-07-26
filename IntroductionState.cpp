#include "IntroductionState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"

#include "MenuState.h"

void IntroductionState::init()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
}

void IntroductionState::react()
{
	if (_simpleKeypad->getPressedKey() != KEY_NONE)
	{
		_program->getStateManager()->changeState(1);
		_buzzer->playOnPress();
	}

	if (_disrupted)
	{
		_lcd->begin();
		_needRedraw = true;
		_disrupted = false;
	}

	if (_needRedraw)
	{
		_lcd->manage(this);
		_needRedraw = false;
	}
}

void IntroductionState::reset()
{

}