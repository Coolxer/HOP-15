#ifndef _MENUSTATE_h
#define _MENUSTATE_h

#include <Arduino.h>

#include "State.h"

#include "SetValueElement.h"

#define ITEM_COUNT 13

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;
class A4988;
class RotaryEncoder;

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
	A4988* _dividerMotor;
	A4988* _tableMotor;
	RotaryEncoder* _rotaryEncoder;

	String _itemNames[ITEM_COUNT];
	ItemBind _itemBinds[ITEM_COUNT];

	byte _itemsCount = ITEM_COUNT;
	byte _selectedIndex = 1;
	bool _isFocused = false;

	SetValueElement _featherAmount;
	SetValueElement _cycleAmount;
	SetValueElement _speed;
	SetValueElement _cutterAngle;

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

	float getValueAtIndex(byte index);

};

#endif

