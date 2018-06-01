#include "SevSegms.h"

SevSegms::SevSegms()
{
	_sevSeg.begin(COMMON_ANODE, _numDigits, _digitPins, _segmentPins);
	_sevSeg.setBrightness(50);
}

void SevSegms::manage(ProgramElement* programElement)
{
	byte feather = programElement->getCurrentFeather();
	byte feathers = programElement->getFeathersCount();
	byte cycle = programElement->getCurrentCycle();
	byte cycles = programElement->getCyclesCount();

	_number = (feathers * cycles) - (feather * cycle) + 1;

	_sevSeg.setNumber(_number, 0);
	_sevSeg.refreshDisplay();
}





