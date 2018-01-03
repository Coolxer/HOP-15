#include "motor.h"

Motor::Motor()
{
	pinMode(enablePin, OUTPUT);
	enable(true);
	stepper.begin(rpm, microsteps);
}

void Motor::move()
{
	stepper.rotate(360);
	//stepper.move(-MOTOR_STEPS * MICROSTEPS);
	delay(2000);
}


void Motor::enable(bool e)
{
	if (e)
		digitalWrite(enablePin, LOW);
	else
		digitalWrite(enablePin, HIGH);

	isEnable = e;
}