#include "buzzer.h"

Buzzer::Buzzer()
{
	pinMode(_buzzerPin, OUTPUT);
}

void Buzzer::playOnPress()
{
	tone(_buzzerPin, 4000);
	delay(80);
	noTone(_buzzerPin);
	delay(80);
}

void Buzzer::playOnFinish()
{
	byte length = 15; // the number of notes
	char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
	byte beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
	byte tempo = 200;

	for (int i = 0; i < length; i++) 
	{
		if (notes[i] == ' ') {
			delay(beats[i] * tempo); // rest
		}
		else {
			playNote(notes[i], beats[i] * tempo);
		}

		// pause between notes
		delay(tempo / 2);
	}
}

void Buzzer::playTone(int tone, int duration)
{
	for (long i = 0; i < duration * 1000L; i += tone * 2) 
	{
		digitalWrite(_buzzerPin, HIGH);
		delayMicroseconds(tone);
		digitalWrite(_buzzerPin, LOW);
		delayMicroseconds(tone);
	}
}

void Buzzer::playNote(char note, int duration) 
{
	char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
	int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

	// play the tone corresponding to the note name
	for (int i = 0; i < 8; i++) 
		if (names[i] == note) 
			playTone(tones[i], duration);
}


