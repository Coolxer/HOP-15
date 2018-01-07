#include "MenuElement.h"

MenuElement::MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, byte itemsCount) : Element(name)
{
	if (itemsCount < 1)
		_itemsCount = 1;
	else
		_itemsCount = itemsCount;

	_items = new Element*[_itemsCount];
}

MenuElement::~MenuElement()
{
	delete[] _items;
}

bool MenuElement::setElement(byte index, Element* element)
{
	if (index >= 0 && index < _itemsCount)
	{
		_items[index] = element;
		return true;
	}

	return false;
}

void MenuElement::react()
{
	if (_simpleKeypad->getPressedKey() == KEY_UP)
	{

	}
	else if (_simpleKeypad->getPressedKey() == KEY_DOWN)
	{

	}
}