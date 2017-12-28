#ifndef lcd_h
#define lcd_h

#include <LiquidCrystal.h>

#include "output.h"

class Lcd : public Output
{
  private:
    LiquidCrystal lcd = LiquidCrystal(12, 11, 5, 4, 3, 2);
  
public:
    Lcd();

    void display(TestElement* element);
};

#endif


