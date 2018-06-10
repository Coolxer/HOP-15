#ifndef _MENUSTATE_h
#define _MENUSTATE_h

#include "State.h"
#include "SetValueElement.h"

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;

struct ItemBind
{
	byte index = 0;
	SetValueElement* item = nullptr;
};

class MenuState : public State
{
private:
	Lcd * _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;

	String* _itemNames;
	ItemBind** _itemBinds;
	void(**_itemCalbacks)(MenuState*);

	byte _itemsCount = 3;
	byte _selectedIndex = 1;
	bool _isFocused = false;

public:
	MenuState(Program* program);
	~MenuState();

	bool setElement(byte index, char* description, void(*callback)(MenuState*));
	bool setElement(byte index, SetValueElement* element);

	virtual void react();

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

