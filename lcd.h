#ifndef lcd_h
#define lcd_h

#include <LiquidCrystal.h>
#include "output.h"

class Lcd : public Output
{
private:
	LiquidCrystal lcd = LiquidCrystal(40, 42, 44, 46, 48, 50);

public:
	Lcd();

	void emit(TestElement* element);
};

#endif


