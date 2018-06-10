#include "SimpleKeypad.h"

#include "MenuState.h"
#include "IntroductionState.h"
#include "ProgramState.h"

Keys SimpleKeypad::getPressedKey()
{
	char key = _keypad.getKey();

	if (key == '*')
		return KEY_ENTER;
	else if (key == '#')
		return KEY_RETURN;
	else if (key == 'A')
		return KEY_UP;
	else if (key == 'D')
		return KEY_DOWN;
	else if (key == '0')
		return KEY_0;
	else if (key == '1')
		return KEY_1;
	else if (key == '2')
		return KEY_2;
	else if (key == '3')
		return KEY_3;
	else if (key == '4')
		return KEY_4;
	else if (key == '5')
		return KEY_5;
	else if (key == '6')
		return KEY_6;
	else if (key == '7')
		return KEY_7;
	else if (key == '8')
		return KEY_8;
	else if (key == '9')
		return KEY_9;
	else
		return KEY_NONE;
}

void SimpleKeypad::manage(ProgramState* programState)
{
	_key = getPressedKey();

	if (programState->isFinished())
	{
		if (_key == KEY_ENTER)
			programState->getElementManager()->popBackFromSelected();
	}
}