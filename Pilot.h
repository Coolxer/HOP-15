#ifndef pilot_h
#define pilot_h

#include <Arduino.h>
//#include <IRremote.h>

class Pilot
{
private:
	byte _irPin;
	//IRrecv* _irrecv;
	//decode_results _results;
public:
	Pilot();
	~Pilot();
	void listening();
};

#endif
