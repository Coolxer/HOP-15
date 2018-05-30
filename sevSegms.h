#ifndef SEVSEGMS_h
#define SEVSEGMS_h

#include <Arduino.h>
#include <LEDDisplay.h>

class SevSegms
{
private:
	LEDDisplay* _led;
	int _digitFlagPins[2] = { 35, 37 };
	int _segmentPins[8] = { 41, 39, 23, 29, 27, 33, 31, 25 };
	int _decimalPointPin = 9;

public:
	SevSegms();
	~SevSegms();

	void clear();
	void show(byte feathers, byte cycles);
	

	
};

#endif


