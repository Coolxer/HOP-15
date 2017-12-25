#ifndef lcd_h
#define lcd_h

#include <LiquidCrystal.h>
class Lcd
{
  private:
    LiquidCrystal m_lcd = LiquidCrystal(12, 11, 5, 4, 3, 2);
  public:
    Lcd();
    void draw();
};

#endif


