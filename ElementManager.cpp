#include "ElementManager.h"

ElementManager::ElementManager()
{
	count = 0;
	elements = nullptr;
}

void ElementManager::resize(size_t size)
{
	if (elements != nullptr)
	{
		Element* resizedElements = new Element[size];

		memcpy(resizedElements, elements, count * sizeof(Element));
	}
	else
		elements = new Element[size];

	count += size - count;
}

void ElementManager::add(Element element)
{
	resize(count + 1);
	elements[count - 1] = element;
}