#include "program.h"
#include <Arduino.h>

Program program;

void setup()
{
	Serial.begin(9600);
	program.init();
}

void loop()
{
	program.step();
}