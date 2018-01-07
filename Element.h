#ifndef _ELEMENT_h
#define _ELEMENT_h

#include <Arduino.h>

#include "input.h"

class Element
{
protected:
	char* _name;
	bool _inited = false;

public:
	Element(char* name) { _name = name; };
	virtual ~Element() {};

	virtual void react() = 0;

	void setName(char* name) { _name = name; };
	char* getName() { return _name; };
};

#endif

