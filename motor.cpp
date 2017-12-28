#include "motor.h"

Motor::Motor()
{
	pinMode(ENABLE, OUTPUT);
	//digitalWrite(ENABLE, LOW);
	enable(true);
	stepper.begin(RPM, MICROSTEPS);
}

void Motor::move()
{
	stepper.rotate(360);

	//stepper.move(-MOTOR_STEPS * MICROSTEPS);

	delay(2000);
}


void Motor::enable(bool e)
{
	if(e)
		digitalWrite(ENABLE, LOW);
	else
		digitalWrite(ENABLE, HIGH);

	isEnable = e;
}