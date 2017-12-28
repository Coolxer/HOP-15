#include "main.h"

Main program = Main();

void setup() 
{
	Serial.begin(9600);
}

void loop() 
{
	program.fixedUpdate();
}
