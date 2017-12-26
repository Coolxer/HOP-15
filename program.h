#ifndef program_h
#define program_h

#include <Arduino.h>

#include "keyPad.h"
#include "lcd.h"
#include "motor.h"
#include "sevSegms.h"

class Program
{
  private:
    KeysController keysController = KeysController();
    Lcd lcd = Lcd();
  public:
  
    void init();
    void step();
};

#endif
