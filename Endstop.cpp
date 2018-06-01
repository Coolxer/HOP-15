#include "Endstop.h"

#include "ProgramElement.h"

Endstop::Endstop(byte ePin)
{
	_ePin = ePin;
	pinMode(_ePin, INPUT_PULLUP);
}

bool Endstop::isClicked()
{
	if (digitalRead(_ePin) == LOW)
		return true;
	else
		return false;
}

void Endstop::manage(ProgramElement* programElement)
{
	if (isClicked())
	{
		//If endstop enters to being pressed - first time this function executed during endstop pressed
		if (!programElement->getInRotationArea())
			programElement->setRotatedInCycle(false);

		programElement->setInRotationArea(true);
	}
	else
		programElement->setInRotationArea(false);
}