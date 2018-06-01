#ifndef endstop_h
#define endstop_h

#include <Arduino.h>

class ProgramElement;

class Endstop
{
private:
	byte _ePin;
public:
	Endstop(byte ePin);
	bool isClicked();

	void manage(ProgramElement* programElement);
};

#endif
