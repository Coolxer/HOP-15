#include "ProgramState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "SimpleKeypad.h"
#include "StepperMotor.h"
#include "DcMotor.h"
#include "Endstop.h"
#include "Relay.h"

void ProgramState::init()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
	_sevSegms = deviceManager->requestSevSegms();
	_dividerEndstop = deviceManager->requestDividerEndstop();
	_dividerMotor = deviceManager->requestDividerMotor(_dividerEndstop);
	_tableEndstop = deviceManager->requestTableEndstop();
	_tablePotentiometer = deviceManager->requestTablePotentiometer();
	_tableMotor = deviceManager->requestTableMotor(_tableEndstop, _tablePotentiometer);
	_relay = deviceManager->requestRelay();

	_currentFeather = 1;
	_currentCycle = 1;
}

void ProgramState::react()
{
	_tableMotor->setSpeed();
	_sevSegms->display(_tableMotor->getSpeed());

	if (_needRedraw)
	{
		_lcd->manage(this);
		_needRedraw = false;
	}

	char key = _simpleKeypad->getPressedKey();

	if(key != KEY_NONE)
		_buzzer->playOnPress();

	if (key == KEY_ENTER)
	{
		if (isFinished())
			_program->getStateManager()->changeState(1);
		else
			togglePause();

		_dividerMotor->enable(false);
		_tableMotor->enable(false);
	}
	else if (key == KEY_RETURN)
	{
		_dividerMotor->enable(false);
		_tableMotor->enable(false);
		_program->getStateManager()->changeState(1);
	}
			
	if (!_inited)
	{
		//_dividerMotor->home();
		_tableMotor->home();

		_rotatedInPeriod = true;
		_isEndstopClickExecuted = true;

		_inited = true;
	}
	else
	{
		if (!_finished && !_paused)
		{
			//Table and divider motor
			if (_tableEndstop->isClicked())
			{
				if (!_isEndstopClickExecuted)
				{
					_isMotorMoveForward = !_isMotorMoveForward;
					_motorAngleRotateSpeed *= -1;

					if (_isMotorMoveForward)
					{
						_currentFeather++;

						if (_currentFeather > _feathersCount)
						{
							_currentFeather = 1;
							_currentCycle++;

							if (_currentCycle > _cyclesCount)
								finish();
						}

						if (!_finished)
						{
							_relay->setHighState(true);
							_dividerMotor->rotate(_rotateAngle);
							_relay->setHighState(false);
						}
						_needRedraw = true;
					}
					_isEndstopClickExecuted = true;
				}
				else
				{
					_dividerMotor->enable(false);
					_tableMotor->move(_motorAngleRotateSpeed);
				}
			}
			else
			{
				_dividerMotor->enable(false);
				_tableMotor->move(_motorAngleRotateSpeed);

				if (_isEndstopClickExecuted)
					_isEndstopClickExecuted = false;
			}
		}

		if (_finished && !_finalized)
		{
			_buzzer->playOnFinish();
			_finalized = true;
		}		
	}
}

void ProgramState::reset()
{
	_needRedraw = true;

	_tableMotor->home();

	_currentFeather = 1;
	_currentCycle = 1;

	_rotatedInPeriod = true;
	_isEndstopClickExecuted = false;
	_isMotorMoveForward = true;
	_motorAngleRotateSpeed = 5;

	_dividerMotorHomed = false;
	_tableMotorHomed = false;

	_inited = false;
	_finished = false;
	_paused = false;

	_finalized = false;
}

bool ProgramState::canChangeFeather()
{
	if (_isEndstopClickExecuted && !_rotatedInPeriod)
		return true;
	return false;
}