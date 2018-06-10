#ifndef program_h
#define program_h

#include "StateManager.h"
#include "DeviceManager.h"

#include "IntroductionState.h"
#include "MenuState.h"
#include "ProgramState.h"

class Program
{
private:
	DeviceManager _deviceManager;
	StateManager _stateManager;

public:
	Program() {};

	void init();
	void step();
};

#endif
