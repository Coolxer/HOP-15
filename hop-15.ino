#include "ScrollValueElement.h"
#include "program.h"

Program program;

void setup()
{
	program.init();
}

void loop()
{
	program.step();
}