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
			_program->getStateManager()->changeState(1);
		}
		else
			togglePause();

		break;
	}
	case KEY_RETURN:
	{
		//If we stopped the program
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

		_currentState = MOVING_FORWARD;

		break;
	}
	case MOVING_FORWARD:
	{
		_tableMotor->enable();
		_dividerMotor->enable();

		if (!forwardEndstopClicked)
		{
			_syncDriver->move(_singleDividerMotorStepCount, _singleTableMotorStepCount);
			//synchronizedMove(1);

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

		if (!backwardEndstopClicked)
		{
			_syncDriver->move(_singleDividerMotorStepCount * -1.0, _singleDividerMotorStepCount * -1.0);
			//synchronizedMove(-1);

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

		_dividerMotor->rotate(_rotateAngle * _proportionOfDividerMotorCircles * -1.0);

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

	Serial.println(_cutterAngle);

	//this should be setting always when we start a program because the cutterAngle would changed
	_singleDividerMotorStepCount = double(_singleTableMotorStepCount) / cos(_cutterAngle * _PI / 180.0);

	Serial.println(_singleDividerMotorStepCount);

	_singleDividerMotorStepCount = round(_singleDividerMotorStepCount / 2) * 2;

	Serial.println(_singleDividerMotorStepCount);

	//Get lowest common divider
	long nwd = NWD(_singleTableMotorStepCount, _singleDividerMotorStepCount);

	Serial.println(nwd);

	_singleTableMotorStepCount /= nwd;
	_singleDividerMotorStepCount /= nwd;

	Serial.println(_singleTableMotorStepCount);
	Serial.println(_singleDividerMotorStepCount);
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
	return (long(a) * long(b)) / NWD(a, b);
}

void ProgramState::synchronizedMove(int x)
{
	int currentStep = 0;
	int step = 8;
	int factor = _singleDividerMotorStepCount / _singleTableMotorStepCount;
	int difference = _singleDividerMotorStepCount % _singleTableMotorStepCount;
	int frequency = (_singleTableMotorStepCount / step) / difference;
	int frequencyCounter = 0;

	int movedTableSteps = 0;
	int movedDividerSteps = 0;

	for (int i = 0; i < _singleTableMotorStepCount; i += step)
	{
		int stepsToRotateDivider = step * factor;

		frequencyCounter++;

		if (frequencyCounter == frequency)
		{
			frequencyCounter = 0;
			stepsToRotateDivider += 1;
		}

		if (movedTableSteps + step > _singleTableMotorStepCount)
		{
			_tableMotor->move((_singleTableMotorStepCount - movedTableSteps) * x);
			movedTableSteps = _singleTableMotorStepCount;
		}
		else
		{
			_tableMotor->move(step * x);
			movedTableSteps += step;
		}
			
		if (movedDividerSteps + stepsToRotateDivider > _singleDividerMotorStepCount)
		{
			_dividerMotor->move((_singleDividerMotorStepCount - movedDividerSteps) * x);
			movedDividerSteps = _singleDividerMotorStepCount;
		}
		else
		{
			_dividerMotor->move(stepsToRotateDivider * x);
			movedDividerSteps += stepsToRotateDivider;
		}
	}

	if (movedDividerSteps < _singleDividerMotorStepCount)
		_dividerMotor->move((_singleDividerMotorStepCount - movedDividerSteps) * x);
}