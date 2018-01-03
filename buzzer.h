#ifndef _BUZZER_h
#define _BUZZER_h

#include <Arduino.h>
#include "output.h"

class Buzzer: public Output
{
private:
	byte buzzerPin = 52;

public:
	Buzzer();

	void emit(TestElement* element);

	void playOnClicked();
	void playOnFinish();
};

#endif

