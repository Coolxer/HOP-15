#ifndef _STATEMANAGER_h
#define _STATEMANAGER_h

#include <Arduino.h>

class State;

class StateManager
{
private:
	byte _index = 0;
	byte _count = 4;
	State* _states[4];

public:
	StateManager();

	State* getCurrent();

	void setState(byte index, State* state);
	void changeState(byte index);
};

#endif

