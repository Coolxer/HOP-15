#ifndef _STATEMANAGER_h
#define _STATEMANAGER_h

#include <Arduino.h>

class Element;

class StateManager
{
private:
	//Count of elements in dynamic array use also as index to last element (stack top)
	byte count;
	Element** elements;

	void resize(byte size);

public:
	StateManager();
	~StateManager();

	Element* getCurrent();

	void pushTop(Element* element);
	void popBack();
};

#endif

