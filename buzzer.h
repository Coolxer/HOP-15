#ifndef _BUZZER_h
#define _BUZZER_h

#include <Arduino.h>

class Buzzer
{
private:
	byte buzzerPin = 52;

public:
	Buzzer();
	void playOnClicked();
};

#endif

