#include "ElementManager.h"

ElementManager::ElementManager()
{
	count = 0;
	//Selected equal -1 means no element currently selected
	selected = -1;
	elements = nullptr;
}

ElementManager::~ElementManager()
{
	for (size_t i = 0; i < count; i++)
		delete elements[i];

	delete[] elements;
}

void ElementManager::resize(size_t size)
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

void ElementManager::add(Element* element)
{
	resize(count + 1);
	elements[count - 1] = element;
}

Element* ElementManager::getCurrent()
{
	//If not elements in manager
	if (selected == -1)
		return nullptr;
	else
	{
		//If right index is selected
		if (selected < count)
			return elements[selected];
		else
			return nullptr;
	}
}