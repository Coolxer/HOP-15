#ifndef _DEVICEMANAGER_h
#define _DEVICEMANAGER_h

#include <Arduino.h>

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "Endstop.h"
#include "RotaryEncoder.h"

#include "./lib/AccelStepper.h"

class DeviceManager
{
private:
	Lcd _lcd = Lcd();
	SimpleKeypad _simpleKeypad = SimpleKeypad();
	Buzzer _buzzer = Buzzer();
	SevSegms _sevSegms = SevSegms();
	Endstop _forwardTableEndstop = Endstop(9);
	Endstop _backwardTableEndstop = Endstop(10);
	AccelStepper _dividerMotor = AccelStepper(1, 3, 6);
	AccelStepper _tableMotor = AccelStepper(1, 4, 7);
	RotaryEncoder _rotaryEncoder = RotaryEncoder();

public:
	DeviceManager() 
	{ 
		_dividerMotor.setEnablePin(8);
		_tableMotor.setEnablePin(8);

		_dividerMotor.enableOutputs(); 
		_tableMotor.enableOutputs();

		_dividerMotor.setMaxSpeed(MAX_SPEED);
		_tableMotor.setMaxSpeed(MAX_SPEED);
	}

	Lcd* requestLcd() { return &_lcd; };
	SimpleKeypad* requestSimpleKeypad() { return &_simpleKeypad; };
	Buzzer* requestBuzzer() { return &_buzzer; };
	SevSegms* requestSevSegms() { return &_sevSegms; };
	Endstop* requestForwardTableEndstop() { return &_forwardTableEndstop; };
	Endstop* requestBackwardTableEndstop() { return &_backwardTableEndstop; };
	AccelStepper* requestDividerMotor() { return &_dividerMotor; };
	AccelStepper* requestTableMotor() { return &_tableMotor; };
	RotaryEncoder* requestRotaryEncoder() { return &_rotaryEncoder; };
};

#endif

