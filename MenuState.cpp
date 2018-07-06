#include "MenuState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"

#include "ProgramState.h"
#include "SetValueElement.h"

MenuState::MenuState(Program* program) : State(program)
{
	DeviceManager* deviceManager = program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();

	_itemNames = new String[_itemsCount];
	_itemBinds = new ItemBind*[_itemsCount];

	for (byte i = 0; i < _itemsCount; i++)
		_itemBinds[i] = nullptr;

	SetValueElement* featherAmount = new SetValueElement("Piora", _lcd, _simpleKeypad, 2, 32, 4, 2);
	SetValueElement* cycleAmount = new SetValueElement("Cykle", _lcd, _simpleKeypad, 1, 16, 1, 1);

	setElement(0, featherAmount);
	setElement(1, cycleAmount);
	setElement(2, "Rozpocznij");
}

MenuState::~MenuState()
{
	DeviceManager* deviceManager = _program->getDeviceManager();

	deviceManager->releaseLcd();
	deviceManager->releaseSimpleKeypad();
	deviceManager->releaseBuzzer();

	delete[] _itemNames;

	for (byte i = 0; i < _itemsCount; i++)
	{
		delete _itemBinds[i];
	}

	delete[] _itemBinds;
}

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

	if (_needRedraw)
	{
		_lcd->manage(this);
		_needRedraw = false;
	}
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
		if(_itemBinds[_selectedIndex]->item != nullptr)
			_itemBinds[_selectedIndex]->item->increase();
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
		if (_itemBinds[_selectedIndex]->item != nullptr)
			_itemBinds[_selectedIndex]->item->decrease();
	}

	_needRedraw = true;
}

void MenuState::enter()
{
	if (_itemBinds[_selectedIndex]->item != nullptr)
		_isFocused = !_isFocused;

	if (_itemBinds[_selectedIndex] == nullptr)
	{
		ProgramState* programState = new ProgramState(getProgram(), getValueAtIndex(0), getValueAtIndex(1));
		getProgram()->getStateManager()->pushBack(programState);
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

const char* MenuState::getCurrentValue()
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

const char* MenuState::getPrevValue()
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

char* MenuState::getTip()
{
	return "A-Gora D-Dol *-Enter";
}

byte MenuState::getValueAtIndex(byte index)
{
	if (_itemBinds[index] != nullptr)
	{
		return _itemBinds[index]->item->getValue();
	}
	else
		return NULL;
}