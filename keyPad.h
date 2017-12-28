#ifndef keyPad_h
#define keyPad_h

#include <Arduino.h>
#include <Keypad.h>

class KeysController
{
  private:
    byte rowPins[4] = {22, 24, 26, 28};
    byte colPins[4] = {30, 32, 34, 36};
     
    char keys[4][4] = { 
      {'1','2','3','A'},
      {'4','5','6','B'},
      {'7','8','9','C'},
      {'*','0','#','D'}
    };

	Keypad m_keyPad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
    
  public:
    KeysController();
    char getPushedKey();
};

#endif
