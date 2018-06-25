#include "SevSegms.h"

#include "ProgramState.h"

SevSegms::SevSegms()
{
	_sevSeg.begin(COMMON_ANODE, _numDigits, _digitPins, _segmentPins);
	_sevSeg.setBrightness(50);
}

void SevSegms::manage(ProgramState* programState)
{
	byte feather = programState->getCurrentFeather();
	byte feathers = programState->getFeathersCount();
	byte cycle = programState->getCurrentCycle();
	byte cycles = programState->getCyclesCount();

	_number = (feathers * cycles) - (feather * cycle) + 1;

	_sevSeg.setNumber(_number, 0);
	_sevSeg.refreshDisplay();
}





