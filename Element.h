#ifndef _ELEMENT_h
#define _ELEMENT_h

#include <Arduino.h>

#include "Input.h"
#include "ElementManager.h"

class Element
{
protected:
	char* _name;
	bool _needRedraw = true;

	ElementManager* _elementManager;

public:
	Element(char* name) { _name = name; _elementManager = nullptr; };
	virtual ~Element() {};

	virtual void react() = 0;

	void setName(char* name) { _name = name; };
	char* getName() { return _name; };

	void setElementManager(ElementManager* elementManager) { _elementManager = elementManager; };
	ElementManager* getElementManager() { return _elementManager; };

	void needRedraw() { _needRedraw = true; };
};

#endif

