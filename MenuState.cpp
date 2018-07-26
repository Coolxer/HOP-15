#include "MenuState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"

#include "ProgramState.h"
#include "SetValueElement.h"

bool MenuState::setElement(byte index, char* description)
{
	if (index >= 0 && index < _itemsCount)
	{
		_itemNames[index] = description;
		return true;
	}

	return false;
}

bool MenuState::setElement(byte index, SetValueElement* element)
{
	if (index >= 0 && index < _itemsCount)
	{
		_itemNames[index] = element->getName();

		_itemBinds[index].index = index;
		_itemBinds[index].item = element;

		return true;
	}

	return false;
}

void MenuState::init()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();

	setElement(0, &_featherAmount);
	setElement(1, &_cycleAmount);
	setElement(2, "Rozpocznij");
}

void MenuState::react()
{
	char key = _simpleKeypad->getPressedKey();

	if (key != KEY_NONE)
		_buzzer->playOnPress();

	if (key == KEY_UP)
		up();
	else if (key == KEY_DOWN)
		down();
	else if (key == KEY_ENTER)
		enter();

	if (_disrupted)
	{
		_lcd->begin();
		_needRedraw = true;
		_disrupted = false;
	}

	if (_needRedraw)
	{
		_lcd->manage(this);
		_needRedraw = false;
	}
}

void MenuState::reset()
{

}

void MenuState::up()
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
		if(_itemBinds[_selectedIndex].index != -1)
			_itemBinds[_selectedIndex].item->increase();
	}

	_needRedraw = true;
}

void MenuState::down()
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
		if (_itemBinds[_selectedIndex].index != -1)
			_itemBinds[_selectedIndex].item->decrease();
	}

	_needRedraw = true;
}

void MenuState::enter()
{
	if (_itemBinds[_selectedIndex].index != -1)
		_isFocused = !_isFocused;

	if (_itemBinds[_selectedIndex].index == -1)
	{
		Program* program = getProgram();

		program->getProgramState()->setFeathers(getValueAtIndex(0));
		program->getProgramState()->setCycles(getValueAtIndex(1));
		program->getProgramState()->reset();

		program->getStateManager()->changeState(2);
	}
	_needRedraw = true;
}

const char* MenuState::getNext()
{
	byte index;

	if (_selectedIndex == _itemsCount - 1)
		index = 0;
	else
		index = _selectedIndex + 1;

	return _itemNames[index].c_str();
}

const char* MenuState::getCurrent()
{
	char valueBuf[20] = { 0 };
	_itemNames[_selectedIndex].toCharArray(valueBuf, 20);

	return _itemNames[_selectedIndex].c_str();
}

const char* MenuState::getPrev()
{
	byte index;

	if (_selectedIndex == 0)
		index = _itemsCount - 1;
	else
		index = _selectedIndex - 1;

	//Serial.println(_itemNames[index]);

	return _itemNames[index].c_str();
}

const char* MenuState::getNextValue()
{
	byte index;

	if (_selectedIndex == _itemsCount - 1)
		index = 0;
	else
		index = _selectedIndex + 1;

	if (_itemBinds[index].index != -1)
	{
		byte value = _itemBinds[index].item->getValue();
		char valueStr[6] = { 0 };
		sprintf(valueStr, "%d", value);
		return valueStr;
	}
		//return _itemBinds[index]->item->getValueStr().c_str();

	return "";
}

const char* MenuState::getCurrentValue()
{
	if (_itemBinds[_selectedIndex].index != -1)
	{
		byte value = _itemBinds[_selectedIndex].item->getValue();
		char valueStr[6] = { 0 };
		sprintf(valueStr, "%d", value);
		return valueStr;
	}
		//return _itemBinds[_selectedIndex]->item->getValueStr().c_str();

	return "";
}

const char* MenuState::getPrevValue()
{
	byte index;

	if (_selectedIndex == 0)
		index = _itemsCount - 1;
	else
		index = _selectedIndex - 1;

	if (_itemBinds[index].index != -1)
	{
		byte value = _itemBinds[index].item->getValue();
		char valueStr[6] = { 0 };
		sprintf(valueStr, "%d", value);
		return valueStr;
	}
		//return _itemBinds[index]->item->getValueStr().c_str();

	return "";
}

char* MenuState::getTip()
{
	return "A-Gora D-Dol *-Enter";
}

byte MenuState::getValueAtIndex(byte index)
{
	if (_itemBinds[index].index != -1)
	{
		return _itemBinds[index].item->getValue();
	}
	else
		return NULL;
}