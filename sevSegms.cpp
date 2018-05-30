#include "sevSegms.h"

SevSegms::SevSegms()
{
	_led = new LEDDisplay(2, _digitFlagPins, _segmentPins, _decimalPointPin);
}

SevSegms::~SevSegms()
{
	delete _led;
}

void SevSegms::clear()
{
	_led->clearDisplay();
}

void SevSegms::show(byte feathers, byte cycles)
{						  
	byte result = feathers * cycles;

	byte unitNumber = result % 10;
	result /= 10;
	byte tensNumber = result % 10;

	
	_led->displayNumber(tensNumber, unitNumber);
	//delay(2);
}





