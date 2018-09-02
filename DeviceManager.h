#ifndef _DEVICEMANAGER_h
#define _DEVICEMANAGER_h

#include <Arduino.h>

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "StepperMotor.h"
#include "Endstop.h"
#include "Relay.h"
#include "Encoder.h"

class DeviceManager
{
private:
	Lcd _lcd = Lcd();
	SimpleKeypad _simpleKeypad = SimpleKeypad();
	Buzzer _buzzer = Buzzer();
	SevSegms _sevSegms = SevSegms();
	Endstop _forwardTableEndstop = Endstop(9);
	Endstop _backwardTableEndstop = Endstop(10);
	StepperMotor _dividerMotor = StepperMotor(200, 6, 3, 8);
	StepperMotor _tableMotor = StepperMotor(200, 7, 4, 8, &_forwardTableEndstop, &_backwardTableEndstop);
	Relay _relay = Relay();
	Encoder _encoder = Encoder();

public:
	DeviceManager() {};

	Lcd* requestLcd() { return &_lcd; };
	SimpleKeypad* requestSimpleKeypad() { return &_simpleKeypad; };
	Buzzer* requestBuzzer() { return &_buzzer; };
	SevSegms* requestSevSegms() { return &_sevSegms; };
	Endstop* requestForwardTableEndstop() { return &_forwardTableEndstop; };
	Endstop* requestBackwardTableEndstop() { return &_backwardTableEndstop; };
	StepperMotor* requestDividerMotor() { return &_dividerMotor; };
	StepperMotor* requestTableMotor() { return &_tableMotor; };
	Relay* requestRelay() { return &_relay; };
	Encoder* requestEncoder() { return &_encoder; };
};

#endif

