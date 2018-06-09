#ifndef program_h
#define program_h

#include "Input.h"
#include "Output.h"
#include "StateManager.h"
#include "DeviceManager.h"
#include "MenuElement.h"
#include "IntroductionElement.h"
#include "ProgramElement.h"

class Program
{
private:
	DeviceManager _deviceManager;
	StateManager _stateManager;

public:
	Program();
	~Program();

	void init();
	void step();
};

#endif
