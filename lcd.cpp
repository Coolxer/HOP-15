#include "lcd.h"

Lcd::Lcd()
{
  lcd.begin(20,4);
}

void Lcd::display(TestElement* element)
{
	lcd.clear();
	lcd.print(element->getMessage());
}

