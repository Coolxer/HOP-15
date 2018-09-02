#ifndef _MENUSTATE_h
#define _MENUSTATE_h

#include <Arduino.h>

#include "State.h"
#include "SetValueElement.h"

#define ITEM_COUNT 7 //there was 7 items

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;
class Encoder;

struct ItemBind
{
	int index = -1;
	SetValueElement* item = nullptr;
};

class MenuState : public State
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	Encoder* _encoder;

	String _itemNames[ITEM_COUNT];
	ItemBind _itemBinds[ITEM_COUNT];

	byte _itemsCount = ITEM_COUNT;
	byte _selectedIndex = 1;
	bool _isFocused = false;

	SetValueElement _featherAmount;
	SetValueElement _cycleAmount;
	SetValueElement _dividerMotorSpeed;

public:
	bool setElement(byte index, char* description);
	bool setElement(byte index, SetValueElement* element);

	virtual void init();
	virtual void react();
	virtual void reset();

	void up();
	void down();
	void enter();
	void back() { _isFocused = false; _needRedraw = true; };

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

