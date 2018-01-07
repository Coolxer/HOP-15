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

public:
	MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, byte itemsCount);
	~MenuElement();

	bool setElement(byte index, Element* element);

	virtual void react();
};

#endif

