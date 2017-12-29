#ifndef _ELEMENT_h
#define _ELEMENT_h

#include <Arduino.h>

#include "input.h"

class Element
{
private:
	char* name;

public:
	Element(char* name) { this->name = name; };
	virtual ~Element() {};

	virtual void react(Input* input) = 0;

	void setName(char* name) { this->name = name; };
	char* getName() { return name; };
};

#endif

