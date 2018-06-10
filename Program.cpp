#include "Program.h"

#include "IntroductionState.h"
#include "MenuState.h"
#include "ProgramState.h"

void Program::init()
{
	IntroductionState* introductionElement = new IntroductionState(this);

	

	_stateManager.add(introductionElement);
	_stateManager.add(menuElement);
	_stateManager.changeElement("intro");
}

void Program::step()
{
	_stateManager.getCurrent()->react();
}

