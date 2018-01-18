#include "MenuElement.h"

MenuElement::MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, byte itemsCount) : Element(name)
{
	if (itemsCount < 1)
		_itemsCount = 1;
	else
		_itemsCount = itemsCount;

	_itemNames = new char*[_itemsCount];
	_itemBinds = new ItemBind[_itemsCount];
}

MenuElement::~MenuElement()
{
	delete[] _itemNames;
	delete[] _itemBinds;
}

bool MenuElement::setElement(byte index, char* description)
{
	if (index >= 0 && index < _itemsCount)
	{
		_itemNames[index] = description;
		return true;
	}

	return false;
}

bool MenuElement::setElement(byte index, SetValueElement* element)
{
	if (index >= 0 && index < _itemsCount)
	{
		ItemBind tmpItemBind;

		tmpItemBind.index = index;
		tmpItemBind.item = element;

		_itemBinds[index] = tmpItemBind;
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
		if (_selectedIndex == 0)
			_selectedIndex = _itemsCount - 1;
		else
			_selectedIndex--;
	}
	else
	{
		if(_itemBinds[_selectedIndex].item != nullptr)
			_itemBinds[_selectedIndex].item->increase();
	}
	
}

void MenuElement::down()
{
	if (!_isFocused)
	{
		if (_selectedIndex == _itemsCount - 1)
			_selectedIndex = 0;
		else
			_selectedIndex++;
	}
	else
	{
		if (_itemBinds[_selectedIndex].item != nullptr)
			_itemBinds[_selectedIndex].item->decrease();
	}
}

void MenuElement::enter()
{
	if (_itemBinds[_selectedIndex].item != nullptr)
		_isFocused = !_isFocused;
}

char* MenuElement::getNext()
{
	byte index;

	if (_selectedIndex == _itemsCount - 1)
		index = 0;
	else
		index = _selectedIndex + 1;

	return _itemNames[index];
}

char* MenuElement::getCurrent()
{
	return _itemNames[_selectedIndex];
}

char* MenuElement::getPrev()
{
	byte index;

	if (_selectedIndex == 0)
		index = _itemsCount - 1;
	else
		index = _selectedIndex - 1;

	return _itemNames[index];
}

char* MenuElement::getNextValue()
{
	byte index;

	if (_selectedIndex == _itemsCount - 1)
		index = 0;
	else
		index = _selectedIndex + 1;

	if (_itemBinds[index].item != nullptr)
	{
		String valueStr = _itemBinds[index].item->getValueStr();
		char valueBuf[6] = { 0 };

		valueStr.toCharArray(valueBuf, 6);

		return valueBuf;
	}

	return "";
}

char* MenuElement::getCurrentValue()
{
	if (_itemBinds[_selectedIndex].item != nullptr)
	{
		String valueStr = _itemBinds[_selectedIndex].item->getValueStr();
		char valueBuf[6] = {0};

		valueStr.toCharArray(valueBuf, 6);

		return valueBuf;
	}

	return "";
}

char* MenuElement::getPrevValue()
{
	byte index;

	if (_selectedIndex == 0)
		index = _itemsCount - 1;
	else
		index = _selectedIndex - 1;

	if (_itemBinds[index].item != nullptr)
	{
		String valueStr = _itemBinds[index].item->getValueStr();
		char valueBuf[6] = { 0 };

		valueStr.toCharArray(valueBuf, 6);

		return valueBuf;
	}
}

char* MenuElement::getTip()
{
	return "Tip message to edit";
}