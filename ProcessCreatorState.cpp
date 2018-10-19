#include "ProcessCreatorState.h"

#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"

void ProcessCreatorState::init()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
}

void ProcessCreatorState::react()
{
	char key = _simpleKeypad->getPressedKey();

	if (key != KEY_NONE)
		_buzzer->playOnPress();

	if(key == KEY_ENTER)
	{
		if (_currentLevel != 3)
		{
			_currentLevel++;
			_changedState = true;
		}
			
		else
			startProgram();

	}
	else if (key == KEY_RETURN)
	{
		if (_currentLevel == 0)
			startProgram();
		else
		{
			_currentLevel--;
			_changedState = true;
		}
			
	}

	switch (_currentLevel)
	{
	case 1:
	{
		if (_changedState)
		{
			_lastValue = _featherAmountElement->getValue();
			_changedState = false;
		}
		
		_featherAmountElement->react();
			
		if (_lastValue != _featherAmountElement->getValue())
		{
			_needRedraw = true;
			_lastValue = _featherAmountElement->getValue();
		}
		
		break;
	}
	case 2:
	{
		if (_changedState)
		{
			_lastValue = _diameterElement->getValue();
			_changedState = false;
		}

		_diameterElement->react();

		if (_lastValue != _diameterElement->getValue())
		{
			_needRedraw = true;
			_lastValue = _diameterElement->getValue();
		}

		break;
	}
	case 3:
	{
		if (_changedState)
		{
			_lastValue = _cutterAngleElement->getValue();
			_changedState = false;
		}

		_cutterAngleElement->react();

		if (_lastValue != _cutterAngleElement->getValue())
		{
			_needRedraw = true;
			_lastValue = _cutterAngleElement->getValue();
		}

		break;
	}
	}

	if (_needRedraw)
	{
		_lcd->manage(this);
		_needRedraw = false;
	}
}

void ProcessCreatorState::reset()
{
	_currentLevel = 0;
}

void ProcessCreatorState::startProgram()
{
	ProgramState* programState = getProgram()->getProgramState();
	programState->reset();

	programState->setFeathers(byte(_featherAmountElement->getValue()));
	//programState->setCycles(byte(_itemBinds[1].item->getValue()));
	programState->setCutterAngle(_cutterAngleElement);
	programState->setDiameter(_diameterElement->getValue());
	//programState->setSpeed(_itemBinds[9].item->getValue());
	programState->set();

	getProgram()->getStateManager()->changeState(2);
}
