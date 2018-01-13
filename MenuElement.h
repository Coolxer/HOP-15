#ifndef _MENUELEMENT_h
#define _MENUELEMENT_h

#include "SetValueElement.h"
#include "lcd.h"
#include "simpleKeypad.h"

class MenuElement : public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;

	SetValueElement** _items;
	byte _itemsCount;
	byte _selectedIndex = 1;
	bool _isFocused = false;

	char* _firstOptionName;
	char* _lastOptionName;

	byte _firstIndex;
	byte _lastIndex;

	bool isIndexPointItem();

public:
	MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, byte itemsCount, char* firstOptionName, char* lastOptionName);
	~MenuElement();

	bool setElement(byte index, SetValueElement* element);

	virtual void react();

	void up();
	void down();
	void enter();
	void back();

	byte getIndexValue() { return _selectedIndex; };

	bool isFirstOption() { _selectedIndex == -1 ? true : false; };
	char* getFirstOptionName() { return _firstOptionName; };
	bool isLastOption() { _selectedIndex == _itemsCount ? true : false; };
	char* getLastOptionName() { return _lastOptionName; };
};

#endif

