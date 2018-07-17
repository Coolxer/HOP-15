#include "SevSegms.h"

#include "ProgramState.h"

SevSegms::SevSegms()
{
	_sevSeg.begin(COMMON_ANODE, _numDigits, _digitPins, _segmentPins);
	_sevSeg.setBrightness(50);
	reset();
}

void SevSegms::display(byte number)
{
	if (number != _previousNumber)
	{
		_number = floor((number * 100) / 255);

		if (_number > 99)
			_number = 99;

		_sevSeg.setNumber(_number, 0);
		_previousNumber = number;
	}
	_sevSeg.refreshDisplay();
}

void SevSegms::reset()
{
	_sevSeg.setChars("");
	_sevSeg.refreshDisplay();
}





