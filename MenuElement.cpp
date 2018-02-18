#include "MenuElement.h"

#include "lcd.h"
#include "simpleKeypad.h"

MenuElement::MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, SevSegms* sevSegms, Motor* motor, Endstop* endstop, byte itemsCount) : Element(name)
{
	_lcd = lcd;
	_simpleKeypad = simpleKeypad;
	_sevSegms = sevSegms;
	_motor = motor;
	_endstop = endstop;

	if (itemsCount < 1)
		_itemsCount = 1;
	else
		_itemsCount = itemsCount;

	_itemNames = new String[_itemsCount];
	_itemBinds = new ItemBind*[_itemsCount];
	_itemCalbacks = new (void(*[3])(MenuElement*));

	for (byte i = 0; i < _itemsCount; i++)
	{
		_itemBinds[i] = nullptr;
		_itemCalbacks[i] = nullptr;
	}
}

MenuElement::~MenuElement()
{
	delete[] _itemNames;

	for (byte i = 0; i < _itemsCount; i++)
	{
		delete _itemBinds[i];
	}

	delete[] _itemBinds;
	delete[] _itemCalbacks;
}

bool MenuElement::setElement(byte index, char* description, void(*callback)(MenuElement*))
{
	if (index >= 0 && index < _itemsCount)
	{
		_itemNames[index] = description;
		_itemCalbacks[index] = callback;
		return true;
	}

	return false;
}

bool MenuElement::setElement(byte index, SetValueElement* element)
{
	if (index >= 0 && index < _itemsCount)
	{
		//TODO check if already exist if yes delete
		ItemBind* tmpItemBind = new ItemBind();

		tmpItemBind->index = index;
		tmpItemBind->item = element;

		_itemNames[index] = element->getName();
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
		if(_itemBinds[_selectedIndex]->item != nullptr)
			_itemBinds[_selectedIndex]->item->increase();
	}

	_needRedraw = true;
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
		if (_itemBinds[_selectedIndex]->item != nullptr)
			_itemBinds[_selectedIndex]->item->decrease();
	}

	_needRedraw = true;
}

void MenuElement::enter()
{
	if (_itemBinds[_selectedIndex]->item != nullptr)
		_isFocused = !_isFocused;

	if (_itemCalbacks[_selectedIndex] != nullptr)
		_itemCalbacks[_selectedIndex](this);

	_needRedraw = true;
}

const char* MenuElement::getNext()
{
	byte index;

	if (_selectedIndex == _itemsCount - 1)
		index = 0;
	else
		index = _selectedIndex + 1;

	return _itemNames[index].c_str();
}

const char* MenuElement::getCurrent()
{
	char valueBuf[20] = { 0 };
	_itemNames[_selectedIndex].toCharArray(valueBuf, 20);

	return _itemNames[_selectedIndex].c_str();
}

const char* MenuElement::getPrev()
{
	byte index;

	if (_selectedIndex == 0)
		index = _itemsCount - 1;
	else
		index = _selectedIndex - 1;

	Serial.println(_itemNames[index]);

	return _itemNames[index].c_str();
}

const char* MenuElement::getNextValue()
{
	byte index;

	if (_selectedIndex == _itemsCount - 1)
		index = 0;
	else
		index = _selectedIndex + 1;

	if (_itemBinds[index] != nullptr)
	{
		byte value = _itemBinds[index]->item->getValue();
		char valueStr[6] = { 0 };
		sprintf(valueStr, "%d", value);
		return valueStr;
	}
		//return _itemBinds[index]->item->getValueStr().c_str();

	return "";
}

const char* MenuElement::getCurrentValue()
{
	if (_itemBinds[_selectedIndex] != nullptr)
	{
		byte value = _itemBinds[_selectedIndex]->item->getValue();
		char valueStr[6] = { 0 };
		sprintf(valueStr, "%d", value);
		return valueStr;
	}
		//return _itemBinds[_selectedIndex]->item->getValueStr().c_str();

	return "";
}

const char* MenuElement::getPrevValue()
{
	byte index;

	if (_selectedIndex == 0)
		index = _itemsCount - 1;
	else
		index = _selectedIndex - 1;

	if (_itemBinds[index] != nullptr)
	{
		byte value = _itemBinds[index]->item->getValue();
		char valueStr[6] = { 0 };
		sprintf(valueStr, "%d", value);
		return valueStr;
	}
		//return _itemBinds[index]->item->getValueStr().c_str();

	return "";
}

char* MenuElement::getTip()
{
	return "Tip message to edit";
}