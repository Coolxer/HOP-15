#include "buzzer.h"

Buzzer::Buzzer()
{
	pinMode(buzzerPin, OUTPUT);
}

void Buzzer::playOnClicked()
{
	tone(buzzerPin, 4000);
	delay(80);
	noTone(buzzerPin);
}

