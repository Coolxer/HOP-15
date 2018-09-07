#include "EncoderState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "RotaryEncoder.h"
#include "lib/A4988.h"

void EncoderState::init()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
	_rotaryEncoder = deviceManager->requestRotaryEncoder();

	_dividerMotor = deviceManager->requestDividerMotor();
	_tableMotor = deviceManager->requestTableMotor();
}

void EncoderState::react()
{
	Serial.println("react");
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

	char key = _simpleKeypad->getPressedKey();

	if (key != KEY_NONE)
		_buzzer->playOnPress();

	if (key == KEY_ENTER)
		_program->getStateManager()->changeState(1);

	_dividerMotor->enable();
	_tableMotor->enable();

	switch (_operation)
	{
		case MOVE_DIVIDER_MOTOR:
		{
			_reading = _rotaryEncoder->read();
			_position += _reading;
			_dividerMotor->move(_reading);
;			break;
		}
		case MOVE_TABLE_MOTOR:
		{
			_reading = _rotaryEncoder->read();
			_position += _reading;
			_tableMotor->move(_reading);
			break;
		}
		case CHANGE_SPEED:
		{
			_reading = _rotaryEncoder->read();
			_speed += _reading;
			break;
		}
		case CHANGE_CUTTER_ANGLE:
		{
			_reading = _rotaryEncoder->read();
			_cutterAngle += _reading;
			break;
		}
	}

	_needRedraw = true;
}

void EncoderState::reset()
{
	_needRedraw = true;

	_position = 0;
}