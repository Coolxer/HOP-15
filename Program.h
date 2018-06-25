#ifndef program_h
#define program_h

#include "StateManager.h"
#include "DeviceManager.h"

class Program
{
private:
	DeviceManager _deviceManager;
	StateManager _stateManager;

public:
	Program() {};

	void init();
	void step();

	DeviceManager* getDeviceManager() { return &_deviceManager; };
	StateManager* getStateManager() { return &_stateManager; };
};

#endif
