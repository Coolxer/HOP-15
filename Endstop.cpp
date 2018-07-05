#include "Endstop.h"

#include "ProgramState.h"

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

void Endstop::manage(ProgramState* ProgramState)
{
	if (isClicked())
	{
		//If endstop enters to being pressed - first time this function executed during endstop pressed
		if (!ProgramState->getInRotationArea())
			ProgramState->setRotatedInCycle(false);

		ProgramState->setInRotationArea(true);
	}
	else
		ProgramState->setInRotationArea(false);
}