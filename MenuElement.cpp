#include "MenuElement.h"

MenuElement::MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, byte itemsCount, char* firstOptionName, char* lastOptionName) : Element(name)
{
	if (itemsCount < 1)
		_itemsCount = 1;
	else
		_itemsCount = itemsCount;

	_items = new SetValueElement*[_itemsCount];

	_firstOptionName = firstOptionName;
	_lastOptionName = lastOptionName;

	if (_firstOptionName != "")
		_firstIndex = -1;
	else
		_firstIndex = 0;

	if (_lastOptionName != "")
		_lastIndex = _itemsCount;
	else
		_lastIndex = _itemsCount - 1;
}

MenuElement::~MenuElement()
{
	delete[] _items;
}

bool MenuElement::isIndexPointItem()
{
	if (_selectedIndex >= 0 && _selectedIndex < _itemsCount)
		return true;
	return false;
}

bool MenuElement::setElement(byte index, SetValueElement* element)
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
	if (_lcd != nullptr && _simpleKeypad != nullptr)
	{
		_simpleKeypad->manage(this);

		if (_needRedraw)
		{
			_lcd->manage(this);
			_needRedraw = false;
		}
	}
}

void MenuElement::up()
{
	if (!_isFocused)
	{
		if (_selectedIndex == _firstIndex)
			_selectedIndex = _lastIndex;
		else
			_selectedIndex--;
	}
	else
	{
		_items[_selectedIndex]->increase();
	}
	
}

void MenuElement::down()
{
	if (!_isFocused)
	{
		if (_selectedIndex == _lastIndex)
			_selectedIndex = _firstIndex;
		else
			_selectedIndex++;
	}
	else
	{
		_items[_selectedIndex]->decrease();
	}
}

void MenuElement::enter()
{
	if (isIndexPointItem())
		_isFocused = !_isFocused;
}

void MenuElement::back()
{

}