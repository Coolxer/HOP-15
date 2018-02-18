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

void SevSegms::show(char* feathers, char* cycles)
{						  
	_led->displayNumber(0, 0);
	//delay(2);
}





