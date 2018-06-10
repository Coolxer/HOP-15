#include "MenuState.h"

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"

#include "SetValueElement.h"

void onProgramStart(MenuState* menuState)
{
	ProgramElement* programElement = new ProgramElement("Program", menuElement->_lcd, menuElement->_simpleKeypad, menuElement->_buzzer, menuElement->_sevSegms, menuElement->_dividerMotor, menuElement->_tableMotor, menuElement->_dividerEndstop, menuElement->_tableEndstop, menuElement->_relay, menuElement->getValueAtIndex(0), menuElement->getValueAtIndex(1));
	menuElement->getElementManager()->add(programElement);
	menuElement->getElementManager()->changeElement("Program");
}

MenuState::MenuState(Program* program) : State(program)
{
	DeviceManager* deviceManager = program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();

	_itemNames = new String[_itemsCount];
	_itemBinds = new ItemBind*[_itemsCount];
	_itemCalbacks = new (void(*[3])(MenuState*));

	for (byte i = 0; i < _itemsCount; i++)
	{
		_itemBinds[i] = nullptr;
		_itemCalbacks[i] = nullptr;
	}

	SetValueElement* featherAmount = new SetValueElement("Piora", _lcd, _simpleKeypad, 2, 32, 4, 2);
	SetValueElement* cycleAmount = new SetValueElement("Cykle", _lcd, _simpleKeypad, 1, 16, 1, 1);

	setElement(0, featherAmount);
	setElement(1, cycleAmount);
	setElement(2, "Rozpocznij", &onProgramStart);
}

MenuState::~MenuState()
{
	delete[] _itemNames;

	for (byte i = 0; i < _itemsCount; i++)
	{
		delete _itemBinds[i];
	}

	delete[] _itemBinds;
	delete[] _itemCalbacks;
}

bool MenuState::setElement(byte index, char* description, void(*callback)(MenuState*))
{
	if (index >= 0 && index < _itemsCount)
	{
		_itemNames[index] = description;
		_itemCalbacks[index] = callback;
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
	if (_lcd != nullptr && _simpleKeypad != nullptr)
	{
		_simpleKeypad->manage(this);

		if (_simpleKeypad->getKey() != KEY_NONE)
			_buzzer->playOnPress();

		if (_needRedraw)
		{
			_lcd->manage(this);
			_needRedraw = false;
		}
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

	if (_itemCalbacks[_selectedIndex] != nullptr)
		_itemCalbacks[_selectedIndex](this);

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