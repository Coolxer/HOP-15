#ifndef _ELEMENTMANAGER_h
#define _ELEMENTMANAGER_h

#include "Element.h"

class ElementManager
{
private:
	//Count of elements in dynamic array
	size_t count;
	//Current selected element index
	int selected;
	Element* elements;

	void resize(size_t size);

public:
	ElementManager();

	void add(Element element);
	Element* getCurrent();
};

#endif

