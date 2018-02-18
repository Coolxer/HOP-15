#include "IntroductionElement.h"

IntroductionElement::IntroductionElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad) : Element(name)
{
	_lcd = lcd;
	_simpleKeypad = simpleKeypad;
}

void IntroductionElement::react()
{
	if (_lcd != nullptr && _simpleKeypad != nullptr)
	{
		_simpleKeypad->manage(this);

		if (_needRedraw)
		{
			_lcd->manage(this);
			_needRedraw = false;
		}
	}
}