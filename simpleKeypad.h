#ifndef simpleKeypad_h
#define simpleKeypad_h

#include <Arduino.h>
#include <Keypad.h>
#include "Config.h"
#include "input.h"

class MenuElement;
class IntroductionElement;
class ProgramElement;

class SimpleKeypad : public Input
{
private:
	byte _rowPins[4] = { 50, 48, 46, 44 };
	byte _colPins[4] = { 42, 40, 38, 36 };

	char _keys[4][4] = {
	  {'1','2','3','A'},
	  {'4','5','6','B'},
	  {'7','8','9','C'},
	  {'*','0','#','D'}
	};

	Keypad _keypad = Keypad(makeKeymap(_keys), _rowPins, _colPins, 4, 4);

	char _key;

public:
	SimpleKeypad() {};
	Keys getPressedKey();

	void manage(MenuElement* menuElement);
	void manage(IntroductionElement* introductionElement);
	void manage(ProgramElement* programElement);

	char getKey() { return _key; };
};

#endif
