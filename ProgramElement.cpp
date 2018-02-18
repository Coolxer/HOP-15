#include "ProgramElement.h"

#include "lcd.h"
#include "simpleKeypad.h"
#include "motor.h"
#include "endstop.h"

ProgramElement::ProgramElement(char* name, Lcd* lcd, SevSegms* sevSegms, SimpleKeypad* simpleKeypad, Motor* dividerMotor, Endstop* tableEndstop, byte feathers, byte cycles) : Element(name)
{
	_lcd = lcd;
	_sevSegms = sevSegms;
	_simpleKeypad = simpleKeypad;
	_dividerMotor = dividerMotor;
	_tableEndstop = tableEndstop;

	_feathers = feathers;
	_cycles = cycles;

	_currentFeather = 1;
	_currentCycle = 1;

	_rotateAngle = 360.0 / _feathers;
}

void ProgramElement::react()
{
	if (_lcd != nullptr && _sevSegms != nullptr && _simpleKeypad != nullptr && _dividerMotor != nullptr)
	{
		_simpleKeypad->manage(this);

		if (!_dividerMotorHomed)
			homeDividerMotor();
		if (!_tableMotorHomed)
			homeTableMotor();

		_tableEndstop->manage(this);

		if (_needRedraw)
		{
			_lcd->manage(this);
			_needRedraw = false;
		}

		if (!_finished)
			_dividerMotor->manage(this);
	}
}

bool ProgramElement::canChangeFeather()
{
	if (_inRotationArea && !_rotatedInCycle)
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