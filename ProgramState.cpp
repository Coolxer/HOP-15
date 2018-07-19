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

	_rotateAngle = 360.0 / _feathersCount;
}

void ProgramState::react()
{
	bool betweenEndstops;
	bool forwardEndstopClicked;
	bool backwardEndstopClicked;

	_tableMotor->setSpeed();
	_sevSegms->display(_tableMotor->getSpeed());

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
			_dividerMotor->enable(false);
			_tableMotor->enable(false);

			//relay te¿ powinnien siê wy³¹czyæ?

			_program->getStateManager()->changeState(1);

			break;
		}
	}

	switch (_currentState)
	{
		case START:
		{
			//Power on table motor to let it home
			_tableMotor->enable(true);

			//Power on divider motor to let it move
			_dividerMotor->enable(false);

			_tableMotor->home();

			_currentState = MOVE_FORWARD;

			break;
		}
		case MOVE_FORWARD:
		{	
			//Check if backward endstop is not still clicked
			betweenEndstops = false;

			//Flag if forward endstop clicked
			forwardEndstopClicked = false;

			_tableMotor->enable(true);
			_dividerMotor->enable(false);

			while (!forwardEndstopClicked)
			{
				_tableMotor->moveForward();

				//If due to moving table motor forward endstop is not clicked it's mean we are betweem them
				if (!_tableEndstop->isClicked())
					betweenEndstops = true;

				//If endstop click again it mean we met forward endstop
				if (_tableEndstop->isClicked() && betweenEndstops)
					forwardEndstopClicked = true;
			}

			_tableMotor->stop();

			_currentState = MOVE_BACKWARD;

			break;
		}
		case MOVE_BACKWARD:
		{	
			//Check if forward endstop is not still clicked
			betweenEndstops = false;
			//Flag if backward endstop clicked
			backwardEndstopClicked = false;

			_tableMotor->enable(true);
			_dividerMotor->enable(false);

			while (!backwardEndstopClicked)//forward?
			{
				_tableMotor->moveBackward();

				//If due to moving table motor backward endstop is not clicked it's mean we are betweem them
				if (!_tableEndstop->isClicked())
					betweenEndstops = true;

				//If endstop click again it mean we met backward endstop
				if (_tableEndstop->isClicked() && betweenEndstops)
					backwardEndstopClicked = true;
			}

			_tableMotor->stop();

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

			//Draw updated feathers and cycles
			_needRedraw = true;

			break;
		}
		case UNLOCK_DIVIDER:
		{
			_tableMotor->enable(true);
			_dividerMotor->enable(true);

			_relay->setHighState(true);

			_currentState = CHANGE_FEATHER;

			break;
		}
		case CHANGE_FEATHER:
		{	
			_tableMotor->enable(true);
			_dividerMotor->enable(true);

			_dividerMotor->rotate(_rotateAngle);

			_currentState = LOCK_DIVIDER;

			break;
		}
		case LOCK_DIVIDER:
		{	
			_tableMotor->enable(true);
			_dividerMotor->enable(true);

			_relay->setHighState(false);

			_currentState = MOVE_FORWARD;

			break;
		}
		case FINISH:
		{	
			_tableMotor->enable(false);
			_dividerMotor->enable(false);

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

	_rotateAngle = 360.0 / _feathersCount;
}

void ProgramState::togglePause()
{
	if (_currentState != PAUSE)
	{
		//Disable motors
		_tableMotor->enable(false);
		_dividerMotor->enable(false);

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