#ifndef _STATEMANAGER_h
#define _STATEMANAGER_h

#include <Arduino.h>

class Element;

class StateManager
{
private:
	//Count of elements in dynamic array
	byte count;
	//Current selected element index
	int selected;
	Element** elements;

	void resize(byte size);
	byte getIndexOfElement(char* name);

public:
	StateManager();
	~StateManager();

	void add(Element* element);
	Element* getCurrent();
	bool changeElement(char* name);
	void next() { selected++; };
	void popBackFromSelected();
};

#endif

