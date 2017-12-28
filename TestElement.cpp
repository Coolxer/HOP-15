#include "TestElement.h"

void TestElement::react(Input* input)
{
	char key = input->getPressedKey();

	if (key == KEY_UP)
		message = "Up pressed";
	else if (key == KEY_DOWN)
		message = "Down pressed";
}