#include "ProgramElement.h"

#include "Lcd.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "SimpleKeypad.h"
#include "StepperMotor.h"
#include "DcMotor.h"
#include "Endstop.h"
#include "Relay.h"

ProgramElement::ProgramElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, Buzzer* buzzer, SevSegms* sevSegms, StepperMotor* dividerMotor, DcMotor* tableMotor, Endstop* dividerEndstop, Endstop* tableEndstop, Relay* relay, byte feathersCount, byte cyclesCount) : Element(name)
{
	_lcd = lcd;
	_simpleKeypad = simpleKeypad;
	_buzzer = buzzer;
	_sevSegms = sevSegms;
	_dividerMotor = dividerMotor;
	_tableMotor = tableMotor;
	_dividerEndstop = dividerEndstop;
	_tableEndstop = tableEndstop;
	_relay = relay;

	_feathersCount = feathersCount;
	_cyclesCount = cyclesCount;

	_currentFeather = 1;
	_currentCycle = 1;

	_rotateAngle = 360.0 / _feathersCount;
}

void ProgramElement::react()
{
	if (_simpleKeypad != nullptr && _dividerMotor != nullptr && _tableMotor != nullptr && _dividerEndstop != nullptr && _tableEndstop != nullptr && _relay != nullptr)
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
}

bool ProgramElement::canChangeFeather()
{
	if (_isEndstopClickExecuted && !_rotatedInPeriod)
		return true;
	return false;
}