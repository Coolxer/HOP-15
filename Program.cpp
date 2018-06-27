#include "Program.h"

#include "IntroductionState.h"
#include "MenuState.h"
#include "ProgramState.h"

void Program::init()
{
	IntroductionState* introductionElement = new IntroductionState(this);

	//_stateManager.pushTop(introductionElement);
	_stateManager.pushBack(introductionElement);
}

void Program::step()
{
	_stateManager.getCurrent()->react();
}

