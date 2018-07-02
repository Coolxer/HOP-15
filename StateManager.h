#ifndef _STATEMANAGER_h
#define _STATEMANAGER_h

#include <Arduino.h>

class State;

class StateManager
{
private:
	//Count of elements in dynamic array use also as index to last element (stack top)
	byte count;
	State** states;

	void resize(byte size);

	void clear();

public:
	StateManager();
	~StateManager();

	State* getCurrent();

	void pushBack(State* state);
	void popBack();

	void changeState(State* state);
};

#endif

