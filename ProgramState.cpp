#include "ProgramState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "SimpleKeypad.h"
#include "StepperMotor.h"
#include "Endstop.h"
#include "Relay.h"

void ProgramState::init()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
	_sevSegms = deviceManager->requestSevSegms();
	_dividerMotor = deviceManager->requestDividerMotor();
	_forwardTableEndstop = deviceManager->requestForwardTableEndstop();
	_backwardTableEndstop = deviceManager->requestBackwardTableEndstop();
	_tableMotor = deviceManager->requestTableMotor();
	_relay = deviceManager->requestRelay();

	_proportionOfMotorCircles = _shiftMotorCircleRadius / _directlyMotorCircleRadius;
	_singleDividerMotorStepCount = _singleTableMotorStepCount / cos(_cutterAngle * PI / 180.0);
}

void ProgramState::react()
{
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

	switch (key)
	{
		case KEY_ENTER:
		{	
			if (_currentState == FINISH)
			{
				//If program finished back to menu
				_program->getStateManager()->changeState(1);
			}
			else
				togglePause();

			break;
		}
		case KEY_RETURN: //Stop
		{
			_dividerMotor->disable();
			_tableMotor->disable();

			_program->getStateManager()->changeState(1);

			break;
		}
	}

	switch (_currentState)
	{
		case START:
		{
			_rotateAngle = 360.0 / (float)_feathersCount;

			_currentState = STARTING;

			break;
		}
		case STARTING:
		{
			//Power on table motor to let it home
			_tableMotor->enable();

			//Power on divider motor
			_dividerMotor->enable();

			if (!_relayHomed)
				_relayHomed = true;
				// _relayHomed = _relay->home();

			if(!_tableMotorHomed)
				_tableMotorHomed = _tableMotor->home();

			if (_tableMotorHomed && _relayHomed)
			{
				if (_testingDividerMotor)
					_currentState = UNLOCK_DIVIDER;
				else
					_currentState = MOVE_FORWARD;
			}

			break;
		}
		case MOVE_FORWARD:
		{	
			betweenEndstops = false;
			forwardEndstopClicked = false;

			_currentState = MOVING_FORWARD;
			_startMillis = millis();

			break;
		}
		case MOVING_FORWARD:
		{
			_tableMotor->enable();
			_dividerMotor->enable();

			if (!forwardEndstopClicked)
			{
				_tableMotor->move(_singleTableMotorStepCount);
				_dividerMotor->move(_singleDividerMotorStepCount);

				//If due to moving table motor forward endstop is not clicked it's mean we are betweem them
				if (!_backwardTableEndstop->isClicked())
					betweenEndstops = true;

				//If endstop click again it mean we met backward endstop
				if (_forwardTableEndstop->isClicked() && betweenEndstops)
					forwardEndstopClicked = true;
			}
			else
			{
				_endMillis = millis();
				_currentState = MOVE_BACKWARD;
			}

			break;
		}
		case MOVE_BACKWARD:
		{	
			betweenEndstops = false;
			backwardEndstopClicked = false;

			_currentState = MOVING_BACKWARD;

			break;
		}
		case MOVING_BACKWARD:
		{
			_tableMotor->enable();
			_dividerMotor->disable();

			if(!backwardEndstopClicked)
			{
				_tableMotor->move(_singleDividerMotorStepCount * -1.0);
				_dividerMotor->move(_singleDividerMotorStepCount * -1.0);

				//If due to moving table motor backward endstop is not clicked it's mean we are betweem them
				if (!_forwardTableEndstop->isClicked())
					betweenEndstops = true;

				//If endstop click again it mean we met backward endstop
				if (_backwardTableEndstop->isClicked() && betweenEndstops)
					backwardEndstopClicked = true;
			}
			else
			{
				_currentFeather++;

				//Start changing feather prodcedure
				_currentState = UNLOCK_DIVIDER;

				//Check if new cycle should begin
				if (_currentFeather > _feathersCount)
				{
					_currentFeather = 1;
					_currentCycle++;

					//Check if all cycles was done and finish on yes
					if (_currentCycle > _cyclesCount)
						_currentState = FINISH;
				}

				if (_testingTableMotor)
				{
					//If we only wanted to test table back to menu
					_dividerMotor->disable();
					_tableMotor->disable();
					_program->getStateManager()->changeState(1);
				}

				//Draw updated feathers and cycles
				_needRedraw = true;
			}

			break;
		}
		case UNLOCK_DIVIDER:
		{
			_tableMotor->enable();
			_dividerMotor->enable();

			_relay->pull();
			//There could be physical disruptions reset Lcd then
			reportDisruption();
			delay(100);

			_currentState = CHANGE_FEATHER;

			break;
		}
		case CHANGE_FEATHER:
		{	
			_tableMotor->enable();
			_dividerMotor->enable();

			_dividerMotor->rotate(_rotateAngle * _proportionOfMotorCircles);

			_currentState = LOCK_DIVIDER;

			break;
		}
		case LOCK_DIVIDER:
		{	
			_tableMotor->enable();
			_dividerMotor->enable();

			delay(100);
			_relay->push();
			//There could be physical disruptions reset Lcd then
			reportDisruption();
			delay(100);

			if (_testingDividerMotor)
			{
				_dividerMotor->disable();
				_tableMotor->disable();
				//If we only wanted to test divider back to menu
				_program->getStateManager()->changeState(1);
			}

			_currentState = MOVE_FORWARD;

			break;
		}
		case FINISH:
		{	
			_tableMotor->disable();
			_dividerMotor->disable();

			break;
		}
	}
}

void ProgramState::reset()
{
	_needRedraw = true;

	_currentState = START;

	_currentFeather = 1;
	_currentCycle = 1;

	_relayHomed = false;
	_tableMotorHomed = false;

	_testingDividerMotor = false;
	_testingTableMotor = false;
}

void ProgramState::togglePause()
{
	_needRedraw = true;
	if (_currentState != PAUSE)
	{
		//Disable motors
		_tableMotor->disable();
		_dividerMotor->disable();

		//Save current state to get it back on unpause
		_savedState = _currentState;
		//Set current state to pause
		_currentState = PAUSE;
	}
	else
	{
		//Back to state before pause
		_currentState = _savedState;
	}
}

bool ProgramState::isPaused()
{
	if (_currentState == PAUSE)
		return true;
	return false;
}

bool ProgramState::isFinished()
{
	if (_currentState == FINISH)
		return true;
	return false;
}