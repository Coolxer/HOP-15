#include "ProgramState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "SimpleKeypad.h"
#include "StepperMotor.h"
#include "Endstop.h"

void ProgramState::init()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
	_sevSegms = deviceManager->requestSevSegms();

	_forwardTableEndstop = deviceManager->requestForwardTableEndstop();
	_backwardTableEndstop = deviceManager->requestBackwardTableEndstop();

	_dividerMotor = deviceManager->requestDividerMotor();
	_tableMotor = deviceManager->requestTableMotor();
	_syncDriver = deviceManager->requestSyncDriver();

	_proportionOfDividerMotorCircles = _shiftMotorCircleRadius / _directlyMotorCircleRadius;
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
				_dividerMotor->disable();
				_tableMotor->disable();
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

			if (!_tableMotorHomed)
			{
				_tableMotor->setRPM(30);

				if (_backwardTableEndstop->isClicked())
					_tableMotorHomed = true;
				else
					_tableMotor->move(-8);
			}

			if (_tableMotorHomed)
			{
				if (_testingHome)
					_program->getStateManager()->changeState(1);

				if (_testingDividerMotor)
					_currentState = CHANGE_FEATHER;
				else
					_currentState = MOVE_FORWARD;
			}

			break;
		}
		case MOVE_FORWARD:
		{	
			betweenEndstops = false;
			forwardEndstopClicked = false;

			_tableMotor->setRPM(50);

			_currentState = MOVING_FORWARD;

			break;
		}
		case MOVING_FORWARD:
		{
			_tableMotor->enable();
			_dividerMotor->enable();

			if (!forwardEndstopClicked)
			{
				//_tableMotor->move(_singleTableMotorStepCount);
				//_dividerMotor->move(_singleDividerMotorStepCount);
				_syncDriver->move(_singleDividerMotorStepCount, _singleTableMotorStepCount);

				//If due to moving table motor forward endstop is not clicked it's mean we are betweem them
				if (!_backwardTableEndstop->isClicked())
					betweenEndstops = true;

				//If endstop click again it mean we met backward endstop
				if (_forwardTableEndstop->isClicked() && betweenEndstops)
					forwardEndstopClicked = true;
			}
			else
			{
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
			_dividerMotor->enable();

			if(!backwardEndstopClicked)
			{
				//_tableMotor->move(_singleDividerMotorStepCount * -1.0);
				//_dividerMotor->move(_singleDividerMotorStepCount * -1.0);

				_syncDriver->move(_singleDividerMotorStepCount * -1.0, _singleDividerMotorStepCount * -1.0);

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

				//change state to CHANGE_FEATHER
				_currentState = CHANGE_FEATHER;

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
		case CHANGE_FEATHER:
		{	
			_tableMotor->enable();
			_dividerMotor->enable();

			delay(100);

			_dividerMotor->rotate(_rotateAngle * _proportionOfDividerMotorCircles);

			if (_testingDividerMotor)
			{
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

	_tableMotorHomed = false;

	_testingDividerMotor = false;
	_testingTableMotor = false;
	_testingHome = false;
}

void ProgramState::togglePause()
{
	_needRedraw = true;
	if (_currentState != PAUSE)
	{
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

void ProgramState::setCutterAngle(float angle)
{
	_cutterAngle = angle;

	//this should be setting always when we start a program because the cutterAngle would changed
	_singleDividerMotorStepCount = double(_singleTableMotorStepCount) / cos(_cutterAngle * _PI / 180.0);

	//Get lowest common divider
	int nww = NWW(_singleTableMotorStepCount, _singleDividerMotorStepCount);
	
	_singleTableMotorStepCount /= nww;
	_singleDividerMotorStepCount /= nww;
}

int ProgramState::NWD(int a, int b)
{
	int pom;

	while (b != 0)
	{
		pom = b;
		b = a % b;
		a = pom;
	}

	return a;
}

int ProgramState::NWW(int a, int b)
{
	return (long(a) * long(b)) / NWD(a, b) ;
}