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

void SevSegms::show(int feathers, int cycles)
{						  
	int result = feathers * cycles;

	int unitNumber = result % 10;
	result /= 10;
	int tensNumber = result % 10;

	
	_led->displayNumber(tensNumber, unitNumber);
	//delay(2);
}





