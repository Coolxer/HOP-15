#include "EncoderState.h"

#include <AccelStepper.h>

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "RotaryEncoder.h"

void EncoderState::init()
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

void EncoderState::react()
{
	char key = _simpleKeypad->getPressedKey();

	if (key != KEY_NONE)
		_buzzer->playOnPress();

	if (key == KEY_ENTER)
		_program->getStateManager()->changeState(1);
	else if (key == KEY_B)
		reportDisruption();

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

	switch (_operation)
	{
		case MOVE_DIVIDER_MOTOR:
		{
			_reading = _rotaryEncoder->read();
			Serial.println(_reading);
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
			break;
		}
		case MOVE_TABLE_MOTOR:
		{
			_reading = _rotaryEncoder->read();

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
			
			break;
		}
	}

	if (_reading != 0)
		_needRedraw = true;

	_reading = 0;
}

void EncoderState::reset()
{
	_needRedraw = true;

	_reading = 0;
	_position = 0;

	_rotaryEncoder->reset();
}