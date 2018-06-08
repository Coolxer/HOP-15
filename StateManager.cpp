#include "StateManager.h"

#include "Element.h"

StateManager::StateManager()
{
	count = 0;
	//Selected equal -1 means no element currently selected
	selected = -1;
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

void StateManager::resize(byte size)
{
	if (elements != nullptr)
	{
		Element** resizedElements = new Element*[size];

		memcpy(resizedElements, elements, count * sizeof(Element));
	}
	else
		elements = new Element*[size];

	count += size - count;
}

byte StateManager::getIndexOfElement(char* name)
{
	for (byte i = 0; i < count; i++)
	{
		if (elements[i]->getName() == name)
		{
			return i;
		}
	}

	return -1;
}

void StateManager::add(Element* element)
{
	for (byte i = 0; i < count; i++)
	{
		if (elements[i] == nullptr)
		{
			elements[i] = element;
			return;
		}
	}

	resize(count + 1);
	elements[count - 1] = element;
	element->setElementManager(this);
}

Element* StateManager::getCurrent()
{
	//If not elements in manager
	if (selected == -1)
		return nullptr;
	else
	{
		//If right index is selected
		if (selected < (int)count)
			return elements[selected];
		else
			return nullptr;
	}
}

bool StateManager::changeElement(char* name)
{
	int index = getIndexOfElement(name);

	if (index != -1)
	{
		selected = index;
		return true;
	}

	return false;
}

void StateManager::popBackFromSelected()
{
	if (selected > 0)
	{
		delete elements[selected];
		selected--;
		elements[selected]->needRedraw();
	}
}