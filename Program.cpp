#include "Program.h"

#include "IntroductionState.h"

void Program::init()
{
	IntroductionState* introductionState = new IntroductionState(this);
	_stateManager.pushBack(introductionState);
}

void Program::step()
{
	_stateManager.getCurrent()->react();
}

