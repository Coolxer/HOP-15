#ifndef _DEVICEMANAGER_h
#define _DEVICEMANAGER_h

#include <Arduino.h>

#include "Lcd.h"
#include "SimpleKeypad.h"
#include "Buzzer.h"
#include "SevSegms.h"
#include "Endstop.h"
#include "RotaryEncoder.h"

#include <MultiStepper.h>
#include <AccelStepper.h>

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
	MultiStepper _multiStepper = MultiStepper();
	RotaryEncoder _rotaryEncoder = RotaryEncoder();

public:
	DeviceManager() { 
		_dividerMotor.setEnablePin(8);
		_tableMotor.setEnablePin(8);

		_dividerMotor.enableOutputs(); 
		_tableMotor.enableOutputs();

		//_dividerMotor.setAcceleration(9000000);
		//_tableMotor.setAcceleration(9000000);

		_dividerMotor.setMaxSpeed(10000);
		_tableMotor.setMaxSpeed(10000);

		_dividerMotor.setSpeed(800);
		_tableMotor.setSpeed(800);

		_multiStepper.addStepper(_tableMotor);
		_multiStepper.addStepper(_dividerMotor);
	}// _dividerMotor.begin(60, 8); _tableMotor.begin(60, 8); _dividerMotor.disable(); _tableMotor.disable(); };

	Lcd* requestLcd() { return &_lcd; };
	SimpleKeypad* requestSimpleKeypad() { return &_simpleKeypad; };
	Buzzer* requestBuzzer() { return &_buzzer; };
	SevSegms* requestSevSegms() { return &_sevSegms; };
	Endstop* requestForwardTableEndstop() { return &_forwardTableEndstop; };
	Endstop* requestBackwardTableEndstop() { return &_backwardTableEndstop; };
	//A4988* requestDividerMotor() { return &_dividerMotor; };
	AccelStepper* requestDividerMotor() { return &_dividerMotor; };
	AccelStepper* requestTableMotor() { return &_tableMotor; };
	MultiStepper* requestMultiStepper() { return &_multiStepper; };
	RotaryEncoder* requestRotaryEncoder() { return &_rotaryEncoder; };
};

#endif

