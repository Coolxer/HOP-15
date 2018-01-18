#ifndef _MENUELEMENT_h
#define _MENUELEMENT_h

#include "SetValueElement.h"
#include "lcd.h"
#include "simpleKeypad.h"

struct ItemBind
{
	byte index = 0;
	SetValueElement* item = nullptr;
};

class MenuElement : public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;

	char** _itemNames;
	ItemBind* _itemBinds;

	byte _itemsCount;
	byte _selectedIndex = 1;
	bool _isFocused = false;

public:
	MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, byte itemsCount);
	~MenuElement();

	bool setElement(byte index, char* description);
	bool setElement(byte index, SetValueElement* element);

	virtual void react();

	void up();
	void down();
	void enter();

	char* getNext();
	char* getCurrent();
	char* getPrev();

	char* getNextValue();
	char* getCurrentValue();
	char* getPrevValue();

	char* getTip();

};

#endif

