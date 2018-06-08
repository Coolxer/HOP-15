#include "StateManager.h"

#include "Element.h"

StateManager::StateManager()
{
	count = 0;
	elements = nullptr;
}

StateManager::~StateManager()
{
	for (byte i = 0; i < count; i++)
	{
		if (elements[i] != nullptr)
			delete elements[i];
	}

	delete[] elements;
}

Element* StateManager::getCurrent()
{
	if (count > 0)
		return elements[count];
	else return nullptr;
}

void StateManager::pushTop(Element* element)
{
	resize(++count);
	elements[count - 1] = element;
	element->setStateManager(this);
}

void StateManager::popBack()
{
	if (count > 0)
	{
		delete elements[count - 1];
		resize(--count);

		if(count > 0)
			elements[count - 1]->needRedraw();
	}
}

void StateManager::resize(byte size)
{
	if (elements != nullptr)
	{
		Element** resizedElements = new Element*[size];
		memcpy(resizedElements, elements, (size - 1) * sizeof(Element));
	}
	else
		elements = new Element*[size];
}