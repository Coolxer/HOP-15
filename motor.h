#ifndef motor_h
#define motor_h

#include <Arduino.h>
#include <BasicStepperDriver.h>
#include <A4988.h>

/*
#define MOTOR_STEPS 200
#define RPM 120

#define MICROSTEPS 1

#define DIR 6
#define STEP 3
#define ENABLE 8
*/

class Motor
{
private:
	byte motorSteps = 200;
	byte rpm = 120;
	byte microsteps = 1;

	byte dirPin = 6;
	byte stepPin = 3;
	byte enablePin = 8;

	BasicStepperDriver stepper = BasicStepperDriver(motorSteps, dirPin, stepPin);

	bool isEnable;

public:
	Motor();
	void move();
	void enable(bool e);
};

#endif
