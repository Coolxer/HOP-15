#ifndef _ELEMENT_h
#define _ELEMENT_h

#include <Arduino.h>

#include "Input.h"
#include "StateManager.h"

class Element
{
protected:
	char* _name;
	bool _needRedraw = true;

	StateManager* _stateManager;

public:
	Element() { _stateManager = nullptr; }
	Element(char* name) { _name = name; _stateManager = nullptr; };
	virtual ~Element() {};

	virtual void react() = 0;

	void setName(char* name) { _name = name; };
	char* getName() { return _name; };

	void setStateManager(StateManager* elementManager) { _stateManager = elementManager; };
	StateManager* getStateManager() { return _stateManager; };

	void needRedraw() { _needRedraw = true; };
};

#endif

