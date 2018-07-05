#include "SevSegms.h"

#include "ProgramState.h"

SevSegms::SevSegms()
{
	_sevSeg.begin(COMMON_ANODE, _numDigits, _digitPins, _segmentPins);
	_sevSeg.setBrightness(50);
}

void SevSegms::display(byte number)
{
	_number = floor((number * 100) / 255);

	if (_number == 100)
		_number = 99;

	_sevSeg.setNumber(_number, 0);
	_sevSeg.refreshDisplay();
}





