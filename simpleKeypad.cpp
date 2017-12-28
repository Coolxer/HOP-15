#include "simpleKeypad.h"

SimpleKeypad::SimpleKeypad()
{
	keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
}

Key SimpleKeypad::getPressedKey()
{
	char key = keypad.getKey();

	if (key == '*')
		return KEY_ENTER;
	else if (key == '#')
		return KEY_RETURN;
	else if (key == 'A')
		return KEY_UP;
	else if (key == 'D')
		return KEY_DOWN;
	else
		return KEY_NONE;
}

