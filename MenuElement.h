#ifndef _MENUELEMENT_h
#define _MENUELEMENT_h

#include "SetValueElement.h"
#include "Element.h"

class Lcd;
class SimpleKeypad;
class Buzzer;
class SevSegms;
class Motor;
class Endstop;

struct ItemBind
{
	byte index = 0;
	SetValueElement* item = nullptr;
};

class MenuElement : public Element
{
private:
	String* _itemNames;
	ItemBind** _itemBinds;
	void(**_itemCalbacks)(MenuElement*);

	byte _itemsCount;
	byte _selectedIndex = 1;
	bool _isFocused = false;

public:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	SevSegms *_sevSegms;
	Motor* _dividerMotor;
	Motor* _tableMotor;
	Endstop* _dividerEndstop;
	Endstop* _tableEndstop;

	MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, Buzzer* buzzer, SevSegms* sevSegms, Motor* dividerMotor, Motor* tableMotor, Endstop* dividerEndstop, Endstop* tableEndstop, byte itemsCount);
	~MenuElement();

	bool setElement(byte index, char* description, void(*callback)(MenuElement*));
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

