#include "lcd.h"

Lcd::Lcd()
{
	lcd.begin(20, 4);
}

void Lcd::emit(TestElement* element)
{
	lcd.clear();
	lcd.print(element->getMessage());
}

