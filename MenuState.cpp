#include "MenuState.h"

#include <AccelStepper.h>

#include "Program.h"
#include "DeviceManager.h"

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "RotaryEncoder.h"

#include "ProgramState.h"
#include "ManualControlState.h"

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
	_featherAmount = SetValueElement("Piora", this, 2, 32, 4, 1);
	_cycleAmount = SetValueElement("Cykle", this, 1, 99, 1, 1);
	
	_speed = SetValueElement("Predkosc", this, 100.0, 10000.0, 800.0, 100.0);
	_cutterAngle = SetValueElement("Kat obrotu", this, 0, 60.0, 30.0, 0.01);
	_diameter = SetValueElement("Srednica", this, 5.0, 100.0, 16.0, 0.01);

	_speed = SetValueElement("Predkosc", this, 100, 3000, 600, 100);

	DeviceManager* deviceManager = _program->getDeviceManager();

	_lcd = deviceManager->requestLcd();
	_simpleKeypad = deviceManager->requestSimpleKeypad();
	_buzzer = deviceManager->requestBuzzer();
	_dividerMotor = deviceManager->requestDividerMotor();
	_tableMotor = deviceManager->requestTableMotor();
	_rotaryEncoder = deviceManager->requestRotaryEncoder();

	setElement(0, &_featherAmount);
	setElement(1, &_cycleAmount);
	setElement(2, &_cutterAngle);
	setElement(3, &_diameter);
	setElement(4, "Rozpocznij");
	setElement(5, "Test podzielnicy");
	setElement(6, "Test stolu");
	setElement(7, "Obroc podziel.");
	setElement(8, "Przesun stol");
	setElement(9, "Wylacz silniki");
	setElement(10, "Ustaw do bazy");
	setElement(11, "Kierunek");
	setElement(12, "Regulacja");
	setElement(13, &_speed);
}

void MenuState::react()
{
	if (_isFocused && _itemBinds[_selectedIndex].index != -1)
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
		else if (key == KEY_DISRUPT)
			reportDisruption();
		else if (key == KEY_RESET)
			resetFunc();
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
	{
		if (_isFocused)
			_itemBinds[_selectedIndex].item->validate();
		else
			_itemBinds[_selectedIndex].item->init();

		_isFocused = !_isFocused;
	}

	//If we starting new program
	if (_selectedIndex == 4)
	{
		ProgramState* programState = getProgram()->getProgramState();
		programState->setFeathers(byte(_itemBinds[0].item->getValue()));
		programState->setCycles(byte(_itemBinds[1].item->getValue()));
		programState->setCutterAngle(_itemBinds[2].item->getValue());
		programState->setDiameter(_itemBinds[3].item->getValue());
		programState->setSpeed(_itemBinds[13].item->getValue());

		programState->reset();


		getProgram()->getStateManager()->changeState(2);
	}
	//If we testing divider
	else if (_selectedIndex == 5)
	{
		ProgramState* programState = getProgram()->getProgramState();
		programState->setFeathers(byte(_itemBinds[0].item->getValue()));
		programState->setCycles(byte(_itemBinds[1].item->getValue()));
		programState->setCutterAngle(_itemBinds[2].item->getValue());
		programState->setDiameter(_itemBinds[3].item->getValue());
		programState->setSpeed(_itemBinds[13].item->getValue());

		programState->reset();

		programState->testDividerMotor();

		getProgram()->getStateManager()->changeState(2);
	}
	//If we testing table
	else if (_selectedIndex == 6)
	{
		ProgramState* programState = getProgram()->getProgramState();
		programState->setFeathers(byte(_itemBinds[0].item->getValue()));
		programState->setCycles(byte(_itemBinds[1].item->getValue()));
		programState->setCutterAngle(_itemBinds[2].item->getValue());
		programState->setDiameter(_itemBinds[3].item->getValue());
		programState->setSpeed(_itemBinds[13].item->getValue());

		programState->reset();
		
		programState->testTableMotor();

		getProgram()->getStateManager()->changeState(2);
	}
	//If we rotating divider
	else if (_selectedIndex == 7)
	{
		ManualControlState* ManualControlState = getProgram()->getManualControlState();
		ManualControlState->reset();
		ManualControlState->setOperation("MOVE_DIVIDER_MOTOR");

		getProgram()->getStateManager()->changeState(3);
	}
	//If we moving table
	else if (_selectedIndex == 8)
	{
		ManualControlState* ManualControlState = getProgram()->getManualControlState();
		ManualControlState->reset();
		ManualControlState->setOperation("MOVE_TABLE_MOTOR");

		getProgram()->getStateManager()->changeState(3);
	}
	//If we disabling motors
	else if (_selectedIndex == 9)
	{
		_dividerMotor->enableOutputs();
		_tableMotor->enableOutputs();
	}
	//If homing table motor
	else if (_selectedIndex == 10)
	{
		ProgramState* programState = getProgram()->getProgramState();
		programState->reset();

		if (!programState->isHomed())
		{
			programState->testHome();
			getProgram()->getStateManager()->changeState(2);
		}		
	}
	//If we changing the direction of rotation
	else if (_selectedIndex == 11)
	{
		ProgramState* programState = getProgram()->getProgramState();

		if (programState->getDirection())
			programState->setDirection(false);
		else
			programState->setDirection(true);
	}

	else if (_selectedIndex == 12)
	{
		ProgramState* programState = getProgram()->getProgramState();
		programState->setFeathers(byte(_itemBinds[0].item->getValue()));
		programState->setCycles(byte(_itemBinds[1].item->getValue()));
		programState->setCutterAngle(_itemBinds[2].item->getValue());
		programState->setDiameter(_itemBinds[3].item->getValue());
		programState->setSpeed(_itemBinds[13].item->getValue());

		programState->reset();

		programState->setRegulation();

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
		float value = _itemBinds[index].item->getValue();
		char valueStr[6] = { 0 };
		strcpy(valueStr, "");
		if(value - int(value) != 0)
			dtostrf(value, 2, 2, &valueStr[strlen(valueStr)]);
		else
			dtostrf(value, 2, 0, &valueStr[strlen(valueStr)]);
		return valueStr;
	}

	return "";
}

const char* MenuState::getCurrentValue()
{
	if (_itemBinds[_selectedIndex].index != -1)
	{
		float value = _itemBinds[_selectedIndex].item->getValue();
		char valueStr[6] = { 0 };
		strcpy(valueStr, "");
		if (value - int(value) != 0)
			dtostrf(value, 2, 2, &valueStr[strlen(valueStr)]);
		else
			dtostrf(value, 2, 0, &valueStr[strlen(valueStr)]);
		return valueStr;
	}

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
		float value = _itemBinds[index].item->getValue();
		char valueStr[6] = { 0 };
		strcpy(valueStr, "");
		if (value - int(value) != 0)
			dtostrf(value, 2, 2, &valueStr[strlen(valueStr)]);
		else
			dtostrf(value, 2, 0, &valueStr[strlen(valueStr)]);
		return valueStr;
	}

	return "";
}

char* MenuState::getTip()
{
	return "A-Gora D-Dol *-Enter";
}

float MenuState::getValueAtIndex(byte index)
{
	if (_itemBinds[index].index != -1)
		return _itemBinds[index].item->getValue();
	else
		return NULL;
}