#ifndef endstop_h
#define endstop_h

#include <Arduino.h>

class ProgramState;

class Endstop
{
private:
	byte _ePin;
public:
	Endstop(byte ePin);
	bool isClicked();

	void manage(ProgramState* ProgramState);
};

#endif
