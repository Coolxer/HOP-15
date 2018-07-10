#ifndef _DEVICEMANAGER_h
#define _DEVICEMANAGER_h

#include <Arduino.h>

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "StepperMotor.h"
#include "DcMotor.h"
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
	Endstop _dividerEndstop = Endstop(10);
	Endstop _tableEndstop = Endstop(9);
	Potentiometer _tablePotentiometer = Potentiometer();
	StepperMotor _dividerMotor = StepperMotor(6, 3, 8, &_dividerEndstop);
	DcMotor _tableMotor = DcMotor(&_tableEndstop, &_tablePotentiometer);
	Relay _relay = Relay();

public:
	DeviceManager() {};

	Lcd* requestLcd() { return &_lcd; };
	SimpleKeypad* requestSimpleKeypad() { return &_simpleKeypad; };
	Buzzer* requestBuzzer() { return &_buzzer; };
	SevSegms* requestSevSegms() { return &_sevSegms; };
	Endstop* requestDividerEndstop() { return &_dividerEndstop; };
	Endstop* requestTableEndstop() { return &_tableEndstop; };
	Potentiometer* requestTablePotentiometer() { return &_tablePotentiometer; };
	StepperMotor* requestDividerMotor(Endstop* dividerEndstop) { return &_dividerMotor; };
	DcMotor* requestTableMotor(Endstop* tableEndstop, Potentiometer* potentiometer) { return &_tableMotor; };
	Relay* requestRelay() { return &_relay; };
};

#endif

