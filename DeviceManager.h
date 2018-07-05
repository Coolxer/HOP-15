#ifndef _DEVICEMANAGER_h
#define _DEVICEMANAGER_h

#include <Arduino.h>

class Lcd;
class SimpleKeypad;
class Buzzer;
class SevSegms;
class StepperMotor;
class DcMotor;
class Endstop;
class Relay;
class Potentiometer;

class DeviceManager
{
private:
	Lcd*  _lcd = nullptr;
	byte _lcdUseCount = 0;

	SimpleKeypad* _simpleKeypad = nullptr;
	byte         _simpleKeypadUseCount = 0;

	Buzzer* _buzzer = nullptr;
	byte   _buzzerUseCount = 0;

	SevSegms* _sevSegms = nullptr;
	byte     _sevSegmsUseCount = 0;

	StepperMotor* _dividerMotor = nullptr;
	byte          _dividerMotorUseCount = 0;

	DcMotor* _tableMotor = nullptr;
	byte     _tableMotorUseCount = 0;

	Endstop* _dividerEndstop = nullptr;
	byte     _dividerEndstopUseCount = 0;

	Endstop* _tableEndstop = nullptr;
	byte     _tableEndstopUseCount = 0;

	Relay* _relay = nullptr;
	byte   _relayUseCount = 0;

	Potentiometer* _tablePotentiometer = nullptr;
	byte           _tablePotentiometerUseCount = 0;

public:
	DeviceManager() {};
	~DeviceManager();

	Lcd* requestLcd();
	void releaseLcd();

	SimpleKeypad* requestSimpleKeypad();
	void          releaseSimpleKeypad();

	Buzzer* requestBuzzer();
	void    releaseBuzzer();

	SevSegms* requestSevSegms();
	void      releaseSevSegms();

	StepperMotor* requestDividerMotor(Endstop* dividerEndstop);
	void          releaseDividerMotor();

	DcMotor* requestTableMotor(Endstop* tableEndstop, Potentiometer* potentiometer);
	void     releaseTableMotor();

	Endstop* requestDividerEndstop();
	void     releaseDividerEndstop();

	Endstop* requestTableEndstop();
	void     releaseTableEndstop();

	Potentiometer* requestTablePotentiometer();
	void           releaseTablePotentiometer();

	Relay* requestRelay();
	void   releaseRelay();
};

#endif

