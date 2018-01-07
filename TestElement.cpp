#include "TestElement.h"

void TestElement::react()
{
	char key = input->getPressedKey();

	if (key == KEY_UP)
	{
		message = "Up pressed";
		return true;
	}
	else if (key == KEY_DOWN)
	{
		message = "Down pressed";
		return true;
	}	

	return false;
}