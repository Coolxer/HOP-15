#ifndef _MENUELEMENT_h
#define _MENUELEMENT_h

#include "Element.h"
#include "lcd.h"
#include "simpleKeypad.h"

class MenuElement : public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;

	Element** _items;
	byte _itemsCount;
	byte _selectedIndex = 1;
	bool _isFocused = false;

public:
	MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, byte itemsCount);
	~MenuElement();

	bool setElement(byte index, Element* element);

	virtual bool input();
	virtual void draw();
};

#endif

