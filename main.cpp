#include "main.h"

void Main::init()
{
 
}

void Main::fixedUpdate()
{
   Serial.println(keysController.getPushedKey());
}

