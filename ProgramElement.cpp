#include "ProgramElement.h"

#include "lcd.h"
#include "buzzer.h"
#include "simpleKeypad.h"
#include "motor.h"
#include "endstop.h"

ProgramElement::ProgramElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, Buzzer* buzzer, SevSegms* sevSegms, Motor* dividerMotor, Motor* tableMotor, Endstop* dividerEndstop, Endstop* tableEndstop, byte feathersCount, byte cyclesCount) : Element(name)
{
	_lcd = lcd;
	_simpleKeypad = simpleKeypad;
	_buzzer = buzzer;
	_sevSegms = sevSegms;
	_dividerMotor = dividerMotor;
	_tableMotor = tableMotor;
	_dividerEndstop = dividerEndstop;
	_tableEndstop = tableEndstop;

	_feathersCount = feathersCount;
	_cyclesCount = cyclesCount;

	_currentFeather = 1;
	_currentCycle = 1;

	_rotateAngle = 360.0 / _feathersCount;
}

void ProgramElement::react()
{
	if (_lcd != nullptr && _simpleKeypad != nullptr && _dividerMotor != nullptr && _tableMotor != nullptr && _dividerEndstop != nullptr && _tableEndstop)
	{
		_simpleKeypad->manage(this);

		//if (_simpleKeypad->getKey() != KEY_NONE)
		//	_buzzer->playOnPress();

		if (_needRedraw)
		{
			_lcd->manage(this);
			_needRedraw = false;
		}

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

							if(!_finished)
								_dividerMotor->rotate(_rotateAngle);

							_needRedraw = true;
						}

						_isEndstopClickExecuted = true;
					}
					else
						_tableMotor->rotate(_motorAngleRotateSpeed);
				}
				else
				{
					_tableMotor->rotate(_motorAngleRotateSpeed);

					if (_isEndstopClickExecuted)
						_isEndstopClickExecuted = false;
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

void ProgramElement::homeDividerMotor()
{
	if (!_dividerEndstop->isClicked())
		_dividerMotor->rotate(-1);
	else
		_dividerMotorHomed = true;

}

void ProgramElement::homeTableMotor()
{
	if (!_tableEndstop->isClicked())
		_tableMotor->rotate(-1);
	else
		_tableMotorHomed = true;
}

void ProgramElement::finish()
{
	_finished = true;
	_buzzer->playOnFinish();
}