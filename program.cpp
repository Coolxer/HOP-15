#include "program.h"

void Program::init()
{
 
}

void Program::step()
{
   Serial.println(keysController.getPushedKey());
}

