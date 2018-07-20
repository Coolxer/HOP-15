#ifndef _MENUSTATE_h
#define _MENUSTATE_h

#include <Arduino.h>

#include "State.h"
#include "SetValueElement.h"

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;

struct ItemBind
{
	int index = -1;
	SetValueElement* item = nullptr;
};

class MenuState : public State
{
private:
	Lcd * _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;

	String _itemNames[3];
	ItemBind _itemBinds[3];

	byte _itemsCount = 3;
	byte _selectedIndex = 1;
	bool _isFocused = false;

	SetValueElement _featherAmount = SetValueElement("Piora", _lcd, _simpleKeypad, 2, 32, 4, 1);
	SetValueElement _cycleAmount = SetValueElement("Cykle", _lcd, _simpleKeypad, 1, 16, 1, 1);

public:
	bool setElement(byte index, char* description);
	bool setElement(byte index, SetValueElement* element);

	virtual void init();
	virtual void react();
	virtual void reset();

	void up();
	void down();
	void enter();

	const char* getNext();
	const char* getCurrent();
	const char* getPrev();

	const char* getNextValue();
	const char* getCurrentValue();
	const char* getPrevValue();

	char* getTip();

	byte getValueAtIndex(byte index);

};

#endif

