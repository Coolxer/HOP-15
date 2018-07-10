#ifndef endstop_h
#define endstop_h

#include <Arduino.h>

class Endstop
{
private:
	byte _pin;
public:
	Endstop(byte pin);
	bool isClicked();
};

#endif
