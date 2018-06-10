#ifndef _MENUELEMENT_h
#define _MENUELEMENT_h

#include "SetValueElement.h"
#include "Element.h"

class Lcd;
class SimpleKeypad;
class Buzzer;
class SevSegms;
class StepperMotor;
class DcMotor;
class Endstop;
class Relay;

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
	StepperMotor* _dividerMotor;
	DcMotor* _tableMotor;
	Endstop* _dividerEndstop;
	Endstop* _tableEndstop;
	Relay* _relay;

	MenuElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, Buzzer* buzzer, SevSegms* sevSegms, StepperMotor* dividerMotor, DcMotor* tableMotor, Endstop* dividerEndstop, Endstop* tableEndstop, Relay* relay, byte itemsCount);
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

