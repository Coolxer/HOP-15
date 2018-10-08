#ifndef program_h
#define program_h

#include "StateManager.h"
#include "DeviceManager.h"

#include "IntroductionState.h"
#include "MenuState.h"
#include "ProgramState.h"
#include "ManualControlState.h"

class Program
{
private:
	DeviceManager _deviceManager;
	StateManager _stateManager;

	IntroductionState _introductionState;
	MenuState _menuState;
	ProgramState _programState;
	ManualControlState _ManualControlState;

public:
	Program() {};

	void init();
	void step();

	DeviceManager* getDeviceManager() { return &_deviceManager; };
	StateManager* getStateManager() { return &_stateManager; };
	ProgramState* getProgramState() { return &_programState; };
	ManualControlState* getManualControlState() { return &_ManualControlState; };
};

#endif
