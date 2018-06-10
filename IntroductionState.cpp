#include "IntroductionState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"

IntroductionState::IntroductionState(Program* program) : State(program)
{
	DeviceManager* deviceManager = program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
}

IntroductionState::~IntroductionState()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	deviceManager->releaseLcd();
	deviceManager->releaseSimpleKeypad();
	deviceManager->releaseBuzzer();
}

void IntroductionState::react()
{
	if (_lcd != nullptr && _simpleKeypad != nullptr)
	{
		_simpleKeypad->manage(this);

		if (_simpleKeypad->getKey() != KEY_NONE)
			_buzzer->playOnPress();

		if (_needRedraw)
		{
			_lcd->manage(this);
			_needRedraw = false;
		}
	}
}