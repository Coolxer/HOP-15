#include "ProgramState.h"

#include <AccelStepper.h>

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
	_multiStepper = deviceManager->requestMultiStepper();

	_proportionOfDividerMotorCircles = _bigGearOfDividerMotor / _smallGearOfDividerMotor;
	_proportionOfTableMotorCircles = _bigGearOfTableMotor / _smallGearOfTableMotor;
}

void ProgramState::react()
{
	char key = _simpleKeypad->getPressedKey();

	//if (key != KEY_NONE)
	//	_buzzer->playOnPress();

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
	case KEY_RETURN:
	{
		//If we stopped the program
		//_dividerMotor->enableOutputs();
		//_tableMotor->enableOutputs();
		_program->getStateManager()->changeState(1);

		break;
	}
	case KEY_DISRUPT:
	{
		reportDisruption();
		break;
	}
	case KEY_RESET:
	{
		resetFunc();
		break;
	}
	}

	_cutterAngleElement->react();
	
	if (key == KEY_UP)
		_cutterAngleElement->increase();
	else if (key == KEY_DOWN)
		_cutterAngleElement->decrease();

	_cutterAngle = _cutterAngleElement->getValue();

	if (_cutterAngle != _lastCutterAngle)
	{
		calcSteps();
		//_needRedraw = true;
		_lastCutterAngle = _cutterAngle;
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
	
	switch (_currentState)
	{
	case START:
	{
		_rotateAngle = 360.0 / (float)_feathersCount;
		_currentState = STARTING;

		_tableMotor->setSpeed(-_tableSpeed);

		break;
	}
	case STARTING:
	{
		_tableMotor->disableOutputs();
		_dividerMotor->disableOutputs();

		if (!_tableMotorHomed)
		{
			if (_backwardTableEndstop->isClicked())
				_tableMotorHomed = true;
			else
				_tableMotor->runSpeed();			
		}

		if (_tableMotorHomed)
		{
			if (_testingHome)
				_program->getStateManager()->changeState(1);

			else if (_testingDividerMotor)
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

		_currentState = MOVING_FORWARD;

		break;
	}
	case MOVING_FORWARD:
	{
		_tableMotor->disableOutputs();
		_dividerMotor->disableOutputs();

		_tableMotor->setSpeed(_tableSpeed);
		_dividerMotor->setSpeed(_dividerSpeed);

		if (!forwardEndstopClicked)
		{
			_tableMotor->runSpeed();

			if(!_testingTableMotor)
				_dividerMotor->runSpeed();
				
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
		_tableMotor->disableOutputs();
		_dividerMotor->disableOutputs();

		_tableMotor->setSpeed(-_tableSpeed);
		_dividerMotor->setSpeed(-_dividerSpeed);

		if (!backwardEndstopClicked)
		{
			_tableMotor->runSpeed();

			if (!_testingTableMotor)
				_dividerMotor->runSpeed();

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
			_dividerMotor->setCurrentPosition(0);
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
				_dividerMotor->disableOutputs();
				_tableMotor->disableOutputs();
				_program->getStateManager()->changeState(1);
			}

			//Draw updated feathers and cycles
			_needRedraw = true;
		}

		break;
	}
	case CHANGE_FEATHER:
	{
		_tableMotor->disableOutputs();
		_dividerMotor->disableOutputs();

		_dividerMotor->move(_rotateAngle * _proportionOfDividerMotorCircles * 200 * 8 / 360);

		while (_dividerMotor->distanceToGo() != 0)
		{
			_dividerMotor->setSpeed(800);
			_dividerMotor->runSpeedToPosition();
		}
		
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
		//_tableMotor->enableOutputs();
		//_dividerMotor->enableOutputs();

		break;
	}
	case PAUSE:
	{
		if (key != KEY_NONE)
			_buzzer->playOnPress();

		if (key == KEY_0)
		{
			_program->getManualControlState()->reset();
			_program->getManualControlState()->setOperation("MOVE_DIVIDER_MOTOR");
			_program->getManualControlState()->setRunningDuringProcess();

			_program->getStateManager()->changeState(3);
		}

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

	_tableCountInMM = 50;

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

void ProgramState::calcSteps()
{
	_dividerCountInMM = _tableCountInMM * tan((_cutterAngle * _PI) / 180.0);

	double circuit = _PI * _diameter;

	double numberOfLaps = _dividerCountInMM / circuit;

	double dividerDegress = numberOfLaps * 360;

	_dividerCountInSteps = (dividerDegress * 1600) / 360.0;

	_dividerCountInSteps *= _proportionOfDividerMotorCircles;
	_tableCountInSteps = _proportionOfTableMotorCircles * _tableCountInMM * 14.63116457257362;

	_multiplier = _dividerCountInSteps / _tableCountInSteps;
	_dividerSpeed = _tableSpeed * _multiplier;
}

void ProgramState::set()
{
	_cutterAngle = _cutterAngleElement->getValue();
	_lastCutterAngle = _cutterAngle;
	calcSteps();
}
