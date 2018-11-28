#include "ProgramState.h"

#include "./lib/AccelStepper.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "SimpleKeypad.h"
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
}

void ProgramState::react()
{
	switch (_currentState)
	{
	case START:
	{
		_lcd->manage(this);
		_rotateAngle = 360.0 / (float)_feathersCount;

		_stepsForFeather = round(-_rotateAngle * DIVIDER_GEARS_PROPORTION * STEPS_PER_DEGREE);

		_tableMotor->setSpeed(-_tableSpeed, _tableStepInterval);

		_dividerMotor->disableOutputs();
		_tableMotor->disableOutputs();

		if (_testingHome)
			home();
		else if (_testingDividerMotor)
			_currentState = CHANGE_FEATHER;
		else if (_regulation)
			_currentState = REGULATION;
		else
			_currentState = MOVE_FORWARD;

		delay(_delay);
		
		break;
	}
	case MOVE_FORWARD:
	{
		betweenEndstops = false;
		forwardEndstopClicked = false;

		if (_turningRight)
			_dividerMotor->setSpeed(_dividerSpeed, _dividerStepInterval);
		else
			_dividerMotor->setSpeed(-_dividerSpeed, _dividerStepInterval);

		_tableMotor->setSpeed(_tableSpeed, _tableStepInterval);
	
		_currentState = MOVING_FORWARD;

		break;
	}
	case MOVING_FORWARD:
	{
		if (!forwardEndstopClicked)
		{
			_dividerMotor->runSpeed();
			_tableMotor->runSpeed();

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
			delay(_delay);
		}

		break;
	}
	case MOVE_BACKWARD:
	{
		betweenEndstops = false;
		backwardEndstopClicked = false;

		if(_turningRight)
			_dividerMotor->setSpeed(-_dividerSpeed, _dividerStepInterval);
		else
			_dividerMotor->setSpeed(_dividerSpeed, _dividerStepInterval);

		_tableMotor->setSpeed(-_tableSpeed, _tableStepInterval);

		_currentState = MOVING_BACKWARD;

		break;
	}
	case MOVING_BACKWARD:
	{
		if (!backwardEndstopClicked)
		{
			_dividerMotor->runSpeed();
			_tableMotor->runSpeed();

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
				_program->getStateManager()->changeState(1);
			}

			//Draw updated feathers and cycles
			_lcd->manage(this);

			delay(_delay);
		}

		break;
	}
	case CHANGE_FEATHER:
	{
		changeFeather();

		_currentState = MOVE_FORWARD;

		break;
	}
	case FINISH:
	{
		if (!ended)
		{
			changeFeather();
			ended = true;
			_lcd->manage(this);
		}
			
		char key = _simpleKeypad->getPressedKey();

		if (key == KEY_ENTER)
		{
			_buzzer->playOnPress();
			_program->getStateManager()->changeState(1);
		}

		break;
	}
	case PAUSE:
	{
		/*
		if (key != KEY_NONE)
			_buzzer->playOnPress();

		if (key == KEY_0)
		{
			_program->getManualControlState()->reset();
			_program->getManualControlState()->setOperation("MOVE_DIVIDER_MOTOR");
			_program->getManualControlState()->setRunningDuringProcess();

			_program->getStateManager()->changeState(3);
		}
		*/

		break;
	}
	case REGULATION:
	{
		int piora = (int)_feathersCount;
		int cykle = (int)_cyclesCount;

		for (int i = 0; i < piora * cykle; i++)
		{
			changeFeather();
			delay(500);
		}

		_program->getStateManager()->changeState(1);
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
	_regulation = false;

	ended = false;

	//some calculations

	calcSteps();
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
	//can tableCountInMM be 1mm 100mm or randomly ? or its just changing the results

	//_tableStepInterval = fabs(1000000.0 / _tableSpeed);

	double tableCountInMM = 50;

	double circuit = PI * _diameter;

	double dividerCountInMM = tableCountInMM * tan((_cutterAngle * PI) / 180.0);

	double numberOfLaps = dividerCountInMM / circuit;

	double dividerDegress = numberOfLaps * 360;

	double dividerCountInSteps = (dividerDegress * 1600) / 360.0;

	dividerCountInSteps *= DIVIDER_GEARS_PROPORTION;
	double tableCountInSteps = TABLE_GEARS_PROPORTION * tableCountInMM * STEPS_PER_MM;

	double multiplier = dividerCountInSteps / tableCountInSteps;

	//jesli stol ma wieksza predkosc to nie dajemy na 1000 tylko np na 800?

	if (multiplier > 1)
	{
		_dividerSpeed = _dividerMaxSpeed * (_maxSpeedPercentage / 100.0); //max_speed
		_tableSpeed = _dividerSpeed / multiplier;
	}
	else
	{
		_tableSpeed = _tableMaxSpeed * (_maxSpeedPercentage / 100.0);
		_dividerSpeed = _tableSpeed * multiplier;
	}

	_dividerStepInterval = round(fabs(1000000.0 / _dividerSpeed));
	_tableStepInterval = round(fabs(1000000.0 / _tableSpeed));

	/*
	unsigned long startTime = millis();
	unsigned long time = startTime;

	while (time - startTime < 1000)
		time = millis();
		*/
	Serial.println(multiplier);
}

void ProgramState::changeFeather()
{
	_dividerMotor->setCurrentPosition(0);

	_dividerMotor->move(-_stepsForFeather);

	while (_dividerMotor->distanceToGo() != 0)
	{
		_dividerMotor->setSpeed(DEFAULT_SPEED, DEFAULT_STEP_INTERVAL);
		_dividerMotor->runSpeedToPosition();
	}

	if (_testingDividerMotor)
	{
		//If we only wanted to test divider back to menu
		_program->getStateManager()->changeState(1);
	}

	delay(_delay);
}

void ProgramState::home()
{
	while(!_tableMotorHomed)
	{
		if (_backwardTableEndstop->isClicked())
			_tableMotorHomed = true;
		else
			_tableMotor->runSpeed();
	}

	_program->getStateManager()->changeState(1);
}
