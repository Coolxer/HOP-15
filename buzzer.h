#ifndef _BUZZER_h
#define _BUZZER_h

#include <Arduino.h>
#include "output.h"

class Buzzer: public Output
{
private:
	byte _buzzerPin = 52;

public:
	Buzzer();

	void emit();

	void playOnClicked();
	void playOnFinish();
};

#endif

