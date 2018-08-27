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
#include "Potentiometer.h"

class DeviceManager
{
private:
	Lcd _lcd = Lcd();
	SimpleKeypad _simpleKeypad = SimpleKeypad();
	Buzzer _buzzer = Buzzer();
	SevSegms _sevSegms = SevSegms();
	Endstop _forwardTableEndstop = Endstop(9);
	Endstop _backwardTableEndstop = Endstop(10);
	Potentiometer _tablePotentiometer = Potentiometer();
	StepperMotor _dividerMotor = StepperMotor(200, 6, 3, 8);
	StepperMotor _tableMotor = StepperMotor(200, 5, 2, 8, &_forwardTableEndstop, &_backwardTableEndstop);
	Relay _relay = Relay();

public:
	DeviceManager() {};

	Lcd* requestLcd() { return &_lcd; };
	SimpleKeypad* requestSimpleKeypad() { return &_simpleKeypad; };
	Buzzer* requestBuzzer() { return &_buzzer; };
	SevSegms* requestSevSegms() { return &_sevSegms; };
	Endstop* requestForwardTableEndstop() { return &_forwardTableEndstop; };
	Endstop* requestBackwardTableEndstop() { return &_backwardTableEndstop; };
	Potentiometer* requestTablePotentiometer() { return &_tablePotentiometer; };
	StepperMotor* requestDividerMotor() { return &_dividerMotor; };
	StepperMotor* requestTableMotor() { return &_tableMotor; };
	Relay* requestRelay() { return &_relay; };
};

#endif

