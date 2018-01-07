#ifndef _SETVALUEELEMENT_h
#define _SETVALUEELEMENT_h

class SetValueElement: public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;

	char* _valueName;

	byte _minValue;
	byte _maxValue;
	byte _currentValue;
	byte _stepValue;

public:
	SetValueElement(char* name,
					Lcd* lcd, SimpleKeypad* simpleKeypad,
					char* valueName, byte minValue, byte maxValue, byte currentValue, byte stepValue) : Element(name);
	~SetValueElement() {};

	virtual void react();
	
};

#endif

