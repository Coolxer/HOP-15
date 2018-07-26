#ifndef _ELEMENT_h
#define _ELEMENT_h

#include <Arduino.h>

#include "Input.h"

class MenuState;

class Element
{
protected:
	char* _name;
	bool _needRedraw = true;

	MenuState* _state;

public:
	Element() {};
	Element(char* name) { _name = name; };
	virtual ~Element() {};

	virtual void react() = 0;

	void setName(char* name) { _name = name; };
	char* getName() { return _name; };

	void needRedraw() { _needRedraw = true; };
};

#endif

