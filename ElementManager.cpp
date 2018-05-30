#include "ElementManager.h"

#include "Element.h"

ElementManager::ElementManager()
{
	count = 0;
	//Selected equal -1 means no element currently selected
	selected = -1;
	elements = nullptr;
}

ElementManager::~ElementManager()
{
	for (byte i = 0; i < count; i++)
	{
		if (elements[i] != nullptr)
			delete elements[i];
	}

	delete[] elements;
}

void ElementManager::resize(byte size)
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

byte ElementManager::getIndexOfElement(char* name)
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

void ElementManager::add(Element* element)
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

Element* ElementManager::getCurrent()
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

bool ElementManager::changeElement(char* name)
{
	int index = getIndexOfElement(name);

	if (index != -1)
	{
		selected = index;
		return true;
	}

	return false;
}

void ElementManager::popBackFromSelected()
{
	if (selected > 0)
	{
		delete elements[selected];
		selected--;
		elements[selected]->needRedraw();
	}
}