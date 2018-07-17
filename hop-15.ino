#include "program.h"

#include <stdlib.h>

Program program;

void setup()
{
	program.init();
}

void loop()
{
	program.step();
}