#ifndef main_h
#define main_h

#include <Arduino.h>

#include "keyPad.h"
#include "lcd.h"
#include "motor.h"
#include "sevSegms.h"

class Main
{
  private:
    KeysController keysController = KeysController();
    Lcd lcd = Lcd();
  public:

    enum state{MAIN_MENU, TEETH_SELECTING, CYCLES_SELECTING, AFK};
  
    void init();
    void fixedUpdate();
};

#endif
