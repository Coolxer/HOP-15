#ifndef _ELEMENTMANAGER_h
#define _ELEMENTMANAGER_h

#include "Element.h"

typedef unsigned int size_t;

class ElementManager
{
private:
	//Count of elements in dynamic array
	size_t count;
	//Current selected element index
	int selected;
	Element** elements;

	void resize(size_t size);
	int getIndexOfElement(char* name);

public:
	ElementManager();
	~ElementManager();

	void add(Element* element);
	Element* getCurrent();
	bool changeElement(char* name);
};

#endif

