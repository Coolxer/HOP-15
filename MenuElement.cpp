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

bool MenuElement::input()
{
	if (_simpleKeypad->getPressedKey() == KEY_RETURN)
	{
		_isFocused = false;
		return true;
	}

	if (_isFocused == true)
	{
		if(_items[_selectedIndex] != nullptr)
			return _items[_selectedIndex]->input();
	}

	if (_simpleKeypad->getPressedKey() == KEY_UP)
	{
		_selectedIndex++;

		if (_selectedIndex < 0)
			_selectedIndex = _itemsCount - 1;

		return true;
	}
	else if (_simpleKeypad->getPressedKey() == KEY_DOWN)
	{
		_selectedIndex--;

		if (_selectedIndex > _itemsCount - 1)
			_selectedIndex = 0;

		return true;
	}
	else if (_simpleKeypad->getPressedKey() == KEY_ENTER)
	{
		_isFocused = true;

		return true;
	}
}

void MenuElement::draw()
{
	_lcd->clearLine(3);
	_lcd->writeLine(3, "(*)POTWIERDZ|(#)WROC");
}