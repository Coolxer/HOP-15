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
	/*
	char key = _simpleKeypad->getPressedKey();

	if (key != KEY_NONE)
		_buzzer->playOnPress();

	if (key == KEY_RETURN)
		_program->getStateManager()->changeState(1);
	//else if (key == KEY_DISRUPT)
	//	reportDisruption();
	//else if (key == KEY_RESET)
	//	resetFunc();
	*/

	char key = _simpleKeypad->getKeyValue();

	if (key != ' ')
		_buzzer->playOnPress();

	if (key != '#')
		_program->getStateManager()->changeState(1);

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

	if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5'
		|| key == '6' || key == '7' || key == '8' || key == '9')
	{
		while (key != '*' && key != '#')
		{
			key = _simpleKeypad->getKeyValue();

			if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != ' ')
				_sNumber += key;
		}
		_stepCount = _sNumber.toInt();

		if (key == '*')
			_moveInSteps = true;
		else if (key == '#')
			_moveInSteps = false;

		_sNumber = "";
	}

	_reading = _rotaryEncoder->read();

	if (key == 'A' || _reading == 1)
		_currentStep = _stepCount;
	else if (key == 'D' || _reading == -1)
		_currentStep = _stepCount * -1;


	if(_operation == "MOVE_DIVIDER_MOTOR")
	{
		if (_moveInSteps)
		{
			_positionInSteps += _currentStep;
			_dividerMotor->move(_currentStep);
		}
		else
		{
			_angleOrmm += _currentStep;
			double _proportionOfDividerMotorCircles = 130.1 / 34.81;
			int valueInSteps = _currentStep * _proportionOfDividerMotorCircles * 200 * 8 / 360;

			_dividerMotor->move(valueInSteps);
		}
		
		while (_dividerMotor->distanceToGo() != 0)
		{
			if (_currentStep > 0)
				_dividerMotor->setSpeed(800);
			else if (_currentStep < 0)
				_dividerMotor->setSpeed(-800);

			_dividerMotor->runSpeedToPosition();
		}
	}
	else if (_operation = "MOVE_TABLE_MOTOR")
	{
		if (_moveInSteps)
		{
			if (_currentStep < 0 && !_backwardTableEndstop->isClicked())
			{
				_positionInSteps += _currentStep;
				_tableMotor->move(_currentStep);
			}

			if (_currentStep > 0 && !_forwardTableEndstop->isClicked())
			{
				_positionInSteps += _currentStep;
				_tableMotor->move(_currentStep);
			}
		}
		else
		{
			double _proportionOfTableMotorCircles = 87 / 16.42;
			double wayInSteps = _currentStep * 14.63116457257362 * _proportionOfTableMotorCircles;
			_tableMotor->move(wayInSteps);
		}

		while (_tableMotor->distanceToGo() != 0)
		{
			if (_currentStep < 0)
				_tableMotor->setSpeed(-800);
			else
				_tableMotor->setSpeed(800);

			_tableMotor->runSpeedToPosition();
		}
	}

	if (_currentStep != 0)
		_needRedraw = true;

	_currentStep = 0;
	_reading = 0;
}

void ManualControlState::reset()
{
	_needRedraw = true;

	//_reading = 0;
	//_position = 0;
	_stepCount = 1;
	_currentStep = 0;

	_lastKeyPressed = ' ';
	_sNumber = "";
	_moveInSteps = true;

	_rotaryEncoder->reset();
}