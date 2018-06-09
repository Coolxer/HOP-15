#include "DeviceManager.h"
#include "ProgramElement.h"
#include "IntroductionElement.h"
#include "program.h"

Program program;

void setup()
{
	//Date rate in bits per seconds for serial data transmission
	Serial.begin(9600);

	program.init();
}

void loop()
{
	program.step();
}