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

ProgramState::ProgramState(Program* program, byte feathersCount, byte cyclesCount) : State(program)
{
	DeviceManager* deviceManager = program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
	_sevSegms = deviceManager->requestSevSegms();
	_dividerMotor = deviceManager->requestDividerMotor();
	_tableMotor = deviceManager->requestTableMotor();
	_dividerEndstop = deviceManager->requestDividerEndstop();
	_tableEndstop = deviceManager->requestTableEndstop();
	_relay = deviceManager->requestRelay();

	_feathersCount = feathersCount;
	_cyclesCount = cyclesCount;

	_currentFeather = 1;
	_currentCycle = 1;

	_rotateAngle = 360.0 / _feathersCount;
}

ProgramState::~ProgramState()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	deviceManager->releaseLcd();
	deviceManager->releaseSimpleKeypad();
	deviceManager->releaseBuzzer();
	deviceManager->releaseSevSegms();
	deviceManager->releaseDividerMotor();
	deviceManager->releaseTableMotor();
	deviceManager->releaseDividerEndstop();
	deviceManager->releaseTableEndstop();
	deviceManager->releaseRelay();
}

void ProgramState::react()
{
	if (_needRedraw)
	{
		_lcd->manage(this);
		_sevSegms->manage(this);
		_needRedraw = false;
	}

	_simpleKeypad->manage(this);

	if (_simpleKeypad->getKey() != KEY_NONE)
		_buzzer->playOnPress();

	if (!_inited)
	{
		_dividerMotor->home();
		_tableMotor->home();

		_rotatedInPeriod = true;
		_isEndstopClickExecuted = true;

		_inited = true;
	}
	else
	{
		if (!_finished)
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
				//else
					//_tableMotor->rotate(_motorAngleRotateSpeed);
			}
			else
			{
				//_tableMotor->rotate(_motorAngleRotateSpeed);

				if (_isEndstopClickExecuted)
					_isEndstopClickExecuted = false;
			}
		}
		else
		{
			if (!_finalized)
			{
				_buzzer->playOnFinish();
				_finalized = true;
			}
		}
				
	}
}

bool ProgramState::canChangeFeather()
{
	if (_isEndstopClickExecuted && !_rotatedInPeriod)
		return true;
	return false;
}