#include "sevSegms.h"

SevSegms::SevSegms()
{
	_sevSeg = new SevSeg();
	_sevSeg->begin(COMMON_ANODE, _numDigits, _digitPins, _segmentPins);
}

SevSegms::~SevSegms()
{
	delete _sevSeg;
}

void SevSegms::manage(ProgramElement* programElement)
{
	byte feather = programElement->getCurrentFeather();
	byte feathers = programElement->getFeathersCount();
	byte cycle = programElement->getCurrentCycle();
	byte cycles = programElement->getCyclesCount();

	_number = (feathers * cycles) - (feather * cycle) + 1;

	_sevSeg->setNumber(_number, 0);
	_sevSeg->refreshDisplay();

	Serial.println(_number);
}





