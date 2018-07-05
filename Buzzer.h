#ifndef _BUZZER_h
#define _BUZZER_h

#include <Arduino.h>

class Buzzer
{
private:
	byte _pin = 52;

	void playTone(int tone, int duration);
	void playNote(char note, int duration);

public:
	Buzzer();

	void playOnPress();
	void playOnFinish();
};

#endif

