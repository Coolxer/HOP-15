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
	_relay = deviceManager->requestRelay();

	setElement(0, &_featherAmount);
	setElement(1, &_cycleAmount);
	setElement(2, "Rozpocznij");
	setElement(3, "Od/blokuj podz.");
	setElement(4, &_dividerMotorSpeed);
	setElement(5, "Test podzielnicy");
	setElement(6, "Test stolu");
}

void MenuState::react()
{
	if (_isFocused)
		_itemBinds[_selectedIndex].item->react();
	else
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
	}

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
	if (_selectedIndex == 0)
		_selectedIndex = _itemsCount - 1;
	else
		_selectedIndex--;

	_needRedraw = true;
}

void MenuState::down()
{
	if (_selectedIndex == _itemsCount - 1)
		_selectedIndex = 0;
	else
		_selectedIndex++;

	_needRedraw = true;
}

void MenuState::enter()
{
	if (_itemBinds[_selectedIndex].index != -1)
		_isFocused = !_isFocused;

	//If we starting new program
	if (_selectedIndex == 2)
	{
		ProgramState* programState = getProgram()->getProgramState();

		//Set divider motor speed from menu option
		getProgram()->getDeviceManager()->requestDividerMotor()->setSpeed(getValueAtIndex(3));
		
		programState->setFeathers(getValueAtIndex(0));
		programState->setCycles(getValueAtIndex(1));
		programState->reset();

		getProgram()->getStateManager()->changeState(2);
	}
	//If we blocking or unblocking divider
	else if (_selectedIndex == 4)
	{
		if (!_relayBlocked)
		{
			_relay->pull();
			_relayBlocked = true;
		}
		else
		{
			_relay->push();
			_relayBlocked = false;
		}
	}
	//If we testing divider
	else if (_selectedIndex == 5)
	{
		ProgramState* programState = getProgram()->getProgramState();

		//Set divider motor speed from menu option
		getProgram()->getDeviceManager()->requestDividerMotor()->setSpeed(getValueAtIndex(3));

		programState->setFeathers(getValueAtIndex(0));
		programState->setCycles(getValueAtIndex(1));
		programState->reset();
		programState->testDividerMotor();

		getProgram()->getStateManager()->changeState(2);
	}
	//If we testing table
	else if (_selectedIndex == 6)
	{
		ProgramState* programState = getProgram()->getProgramState();

		//Set divider motor speed from menu option
		getProgram()->getDeviceManager()->requestDividerMotor()->setSpeed(getValueAtIndex(3));

		programState->setFeathers(getValueAtIndex(0));
		programState->setCycles(getValueAtIndex(1));
		programState->reset();
		programState->testTableMotor();

		getProgram()->getStateManager()->changeState(2);
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