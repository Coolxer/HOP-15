#ifndef _ELEMENTMANAGER_h
#define _ELEMENTMANAGER_h

#include <Arduino.h>
#include "Element.h"


class ElementManager
{
private:
	//Count of elements in dynamic array
	byte count;
	//Current selected element index
	int selected;
	Element** elements;

	void resize(byte size);
	int getIndexOfElement(char* name);

public:
	ElementManager();
	~ElementManager();

	void add(Element* element);
	Element* getCurrent();
	bool changeElement(char* name);
};

#endif

