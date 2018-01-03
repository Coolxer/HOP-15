#include "buzzer.h"

Buzzer::Buzzer()
{
	pinMode(buzzerPin, OUTPUT);
}

void Buzzer::emit(TestElement* element)
{

}

void Buzzer::playOnClicked()
{
	tone(buzzerPin, 4000);
	delay(80);
	noTone(buzzerPin);
}

void Buzzer::playOnFinish()
{

}


