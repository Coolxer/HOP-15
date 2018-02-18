#include "buzzer.h"

Buzzer::Buzzer()
{
	pinMode(_buzzerPin, OUTPUT);
}

void Buzzer::emit()
{

}

void Buzzer::playOnClicked()
{
	tone(_buzzerPin, 4000);
	delay(80);
	noTone(_buzzerPin);
	delay(80);
}

void Buzzer::playOnFinish()
{

}


