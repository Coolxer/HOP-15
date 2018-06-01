#ifndef SEVSEGMS_h
#define SEVSEGMS_h

#include <Arduino.h>
#include <SevSeg.h>
#include "ProgramElement.h"

class SevSegms
{
private:

	SevSeg _sevSeg;
	
	byte _numDigits = 2;
	byte _digitPins[2] = { 37, 35 };
	byte _segmentPins[8] = { 41, 39, 23, 29, 27, 33, 31, 25 };

	byte _number;

public:
	SevSegms();

	void manage(ProgramElement* programElement);
	
};

#endif


