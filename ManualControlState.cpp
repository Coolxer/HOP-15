#include "ManualControlState.h"

#include <AccelStepper.h>

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "RotaryEncoder.h"

void ManualControlState::init()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
	_rotaryEncoder = deviceManager->requestRotaryEncoder();

	_dividerMotor = deviceManager->requestDividerMotor();
	_tableMotor = deviceManager->requestTableMotor();

	_forwardTableEndstop = deviceManager->requestForwardTableEndstop();
	_backwardTableEndstop = deviceManager->requestBackwardTableEndstop();
}

void ManualControlState::react()
{
	char key = _simpleKeypad->getPressedKey();

	if (key != KEY_NONE)
		_buzzer->playOnPress();

	if (key == KEY_RETURN)
		_program->getStateManager()->changeState(1);
	else if (key == KEY_DISRUPT)
		reportDisruption();
	else if (key == KEY_RESET)
		resetFunc();

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

	_dividerMotor->disableOutputs();
	_tableMotor->disableOutputs();

	if(_operation == "MOVE_DIVIDER_MOTOR")
	{



		_reading = _rotaryEncoder->read();

		if (key == KEY_UP)
			_reading = _rotaryEncoder->getChangeAmount();
		else if (key == KEY_DOWN)
			_reading = _rotaryEncoder->getChangeAmount() * -1.0;
		

		_position += _reading;
		_dividerMotor->move(_reading);
		while (_dividerMotor->distanceToGo() != 0)
		{
			if (_reading > 0)
				_dividerMotor->setSpeed(800);
			else if (_reading < 0)
				_dividerMotor->setSpeed(-800);

			_dividerMotor->runSpeedToPosition();
		}	
	}
	else if (_operation = "MOVE_TABLE_MOTOR")
	{
		_reading = _rotaryEncoder->read();

		if (key == KEY_UP)
			_reading = _rotaryEncoder->getChangeAmount();
		else if (key == KEY_DOWN)
			_reading = _rotaryEncoder->getChangeAmount() * -1.0;

		if (_reading < 0 && !_backwardTableEndstop->isClicked())
		{
			_position += _reading;
			_tableMotor->move(_reading);
			while (_tableMotor->distanceToGo() != 0)
			{	
				_tableMotor->setSpeed(-800);
				_tableMotor->runSpeedToPosition();
			}
		}

		if (_reading > 0 && !_forwardTableEndstop->isClicked())
		{
			_position += _reading;
			_tableMotor->move(_reading);
			while (_tableMotor->distanceToGo() != 0)
			{
				_tableMotor->setSpeed(800);
				_tableMotor->runSpeedToPosition();
			}
		}
	}
}

	if (_reading != 0)
		_needRedraw = true;

	_reading = 0;
}

void ManualControlState::reset()
{
	_needRedraw = true;

	_reading = 0;
	_position = 0;
	_value = 1;

	_lastKeyPressed = ' ';

	_rotaryEncoder->reset();
}