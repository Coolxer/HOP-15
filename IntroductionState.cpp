#include "IntroductionElement.h"

IntroductionElement::IntroductionElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, Buzzer* buzzer) : Element(name)
{
	_lcd = lcd;
	_simpleKeypad = simpleKeypad;
	_buzzer = buzzer;
}

void IntroductionElement::react()
{
	if (_lcd != nullptr && _simpleKeypad != nullptr)
	{
		_simpleKeypad->manage(this);

		if (_simpleKeypad->getKey() != KEY_NONE)
			_buzzer->playOnPress();

		if (_needRedraw)
		{
			_lcd->manage(this);
			_needRedraw = false;
		}
	}
}