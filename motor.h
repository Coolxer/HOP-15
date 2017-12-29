#ifndef motor_h
#define motor_h

#include <Arduino.h>

#include <BasicStepperDriver.h>
#include <A4988.h>

#define MOTOR_STEPS 200
#define RPM 120

#define MICROSTEPS 1

//#define DIR 6
//#define STEP 3

#define DIR 6
#define STEP 3
#define ENABLE 8


class Motor
{
	private:
		BasicStepperDriver stepper = BasicStepperDriver(MOTOR_STEPS, DIR, STEP);

		bool isEnable;

	public:
		Motor();
		void move();

		void enable(bool e);
};

#endif
