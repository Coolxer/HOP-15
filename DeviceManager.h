#ifndef _DEVICEMANAGER_h
#define _DEVICEMANAGER_h

#include <Arduino.h>

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "lib/A4988.h"
#include "lib/SyncDriver.h"
#include "Endstop.h"

class DeviceManager
{
private:
	Lcd _lcd = Lcd();
	SimpleKeypad _simpleKeypad = SimpleKeypad();
	Buzzer _buzzer = Buzzer();
	SevSegms _sevSegms = SevSegms();
	Endstop _forwardTableEndstop = Endstop(9);
	Endstop _backwardTableEndstop = Endstop(10);
	A4988 _dividerMotor = A4988(200, 6, 3, 8);
	A4988 _tableMotor = A4988(200, 7, 4, 8, &_forwardTableEndstop);
	SyncDriver _syncDriver = SyncDriver(_dividerMotor, _tableMotor);

public:
	DeviceManager() {};

	Lcd* requestLcd() { return &_lcd; };
	SimpleKeypad* requestSimpleKeypad() { return &_simpleKeypad; };
	Buzzer* requestBuzzer() { return &_buzzer; };
	SevSegms* requestSevSegms() { return &_sevSegms; };
	Endstop* requestForwardTableEndstop() { return &_forwardTableEndstop; };
	Endstop* requestBackwardTableEndstop() { return &_backwardTableEndstop; };
	A4988* requestDividerMotor() { return &_dividerMotor; };
	A4988* requestTableMotor() { return &_tableMotor; };
	SyncDriver* requestSyncDriver() { return &_syncDriver; };
};

#endif

