#include "ManualControlState.h"

#include "./lib/AccelStepper.h"

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

	if (key == KEY_ENTER)
	{
		if (!_runningDuringProcess)
			_program->getStateManager()->changeState(1);
		else
			_program->getStateManager()->changeState(2);
	}
		

	else if (key == KEY_DISRUPT)
	{
		if (!_moveInSteps)
		{
			_moveInSteps = true;
			_needRedraw = true;
		}

	}
		
	else if (key == KEY_RESET)
	{
		if (_moveInSteps)
		{
			_moveInSteps = false;
			_needRedraw = true;
		}
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

	_dividerMotor->disableOutputs();
	_tableMotor->disableOutputs();

	if (key == KEY_1 || key == KEY_2 || key == KEY_3 || key == KEY_4 || key == KEY_5
		|| key == KEY_6 || key == KEY_7 || key == KEY_8 || key == KEY_9)
	{
		_changingStepCount = true;
		switch (key)
		{
		case KEY_1:
			_sNumber = "1";
			break;
		case KEY_2:
			_sNumber = "2";
			break;
		case KEY_3:
			_sNumber = "3";
			break;
		case KEY_4:
			_sNumber = "4";
			break;
		case KEY_5:
			_sNumber = "5";
			break;
		case KEY_6:
			_sNumber = "6";
			break;
		case KEY_7:
			_sNumber = "7";
			break;
		case KEY_8:
			_sNumber = "8";
			break;
		case KEY_9:
			_sNumber = "9";
			break;
		}
		_stepCount = _sNumber.toInt();
		_lcd->manage(this);

		while (key != KEY_ENTER)
		{
			key = _simpleKeypad->getPressedKey();

			if (key != KEY_NONE)
				_buzzer->playOnPress();

			if (key != KEY_UP && key != KEY_DISRUPT && key != KEY_RESET && key != KEY_DOWN && key != KEY_NONE)
			{
				switch (key)
				{
				case KEY_0:
					_sNumber += "0";
					break;
				case KEY_1:
					_sNumber + "1";
					break;
				case KEY_2:
					_sNumber += "2";
					break;
				case KEY_3:
					_sNumber += "3";
					break;
				case KEY_4:
					_sNumber += "4";
					break;
				case KEY_5:
					_sNumber += "5";
					break;
				case KEY_6:
					_sNumber += "6";
					break;
				case KEY_7:
					_sNumber += "7";
					break;
				case KEY_8:
					_sNumber += "8";
					break;
				case KEY_9:
					_sNumber += "9";
					break;
				}
				_stepCount = _sNumber.toInt();
				_lcd->manage(this);
			}
		}
		_changingStepCount = false;
		_stepCount = _sNumber.toInt();

		_lcd->manage(this);

		_sNumber = "";
	}

	_reading = _rotaryEncoder->read();

	if (key == KEY_UP|| _reading == 1)
		_currentStep = _stepCount;
	else if (key == KEY_DOWN || _reading == -1)
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
			int valueInSteps = _currentStep * DIVIDER_GEARS_PROPORTION * STEPS_FOR_ONE_DEGREE;

			_dividerMotor->move(valueInSteps);
		}
		
		while (_dividerMotor->distanceToGo() != 0)
		{
			if (_currentStep > 0)
				_dividerMotor->setSpeed(DEFAULT_SPEED, DEFAULT_STEP_INTERVAL);
			else if (_currentStep < 0)
				_dividerMotor->setSpeed(-DEFAULT_SPEED, DEFAULT_STEP_INTERVAL);

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
			double wayInSteps = _currentStep * NUMBER_OF_STEPS_PER_MM * TABLE_GEARS_PROPORTION;
			_tableMotor->move(wayInSteps);
		}

		while (_tableMotor->distanceToGo() != 0)
		{
			if (_currentStep < 0)
				_tableMotor->setSpeed(-DEFAULT_SPEED, DEFAULT_STEP_INTERVAL);
			else
				_tableMotor->setSpeed(DEFAULT_SPEED, DEFAULT_STEP_INTERVAL);

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

	_positionInSteps = 0;
	_angleOrmm = 0;

	_stepCount = 1;
	_currentStep = 0;

	_lastKeyPressed = ' ';
	_sNumber = "";

	_moveInSteps = true;
	_changingStepCount = false;
	_runningDuringProcess = false;

	_rotaryEncoder->reset();
}