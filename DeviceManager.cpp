#include "DeviceManager.h"

#include "SimpleKeypad.h"
#include "Lcd.h"
#include "SevSegms.h"
#include "Buzzer.h"
#include "StepperMotor.h"
#include "DcMotor.h"
#include "Endstop.h"
#include "Relay.h"
#include "Potentiometer.h"

DeviceManager::~DeviceManager()
{
	if (_lcd != nullptr) delete _lcd;
	if (_simpleKeypad != nullptr) delete _simpleKeypad;
	if (_buzzer != nullptr) delete _buzzer;
	if (_sevSegms != nullptr) delete _sevSegms;
	if (_dividerMotor != nullptr) delete _dividerMotor;
	if (_tableMotor != nullptr) delete _tableMotor;
	if (_dividerEndstop != nullptr) delete _dividerEndstop;
	if (_tableEndstop != nullptr) delete _tableEndstop;
	if (_relay != nullptr) delete _relay;
}

Lcd* DeviceManager::requestLcd()
{
	_lcdUseCount++;

	if (_lcd == nullptr)
		_lcd = new Lcd();
	
	return _lcd;
}

void DeviceManager::releaseLcd()
{
	_lcdUseCount--;

	if (_lcdUseCount == 0)
	{
		delete _lcd;
		_lcd = nullptr;
	}	
}

SimpleKeypad* DeviceManager::requestSimpleKeypad()
{
	_simpleKeypadUseCount++;

	if (_simpleKeypad == nullptr)
		_simpleKeypad = new SimpleKeypad();

	return _simpleKeypad;
}

void DeviceManager::releaseSimpleKeypad()
{
	_simpleKeypadUseCount--;

	if (_simpleKeypadUseCount == 0)
	{
		delete _simpleKeypad;
		_simpleKeypad = nullptr;
	}
}

Buzzer* DeviceManager::requestBuzzer()
{
	_buzzerUseCount++;

	if (_buzzer == nullptr)
		_buzzer = new Buzzer();

	return _buzzer;
}

void DeviceManager::releaseBuzzer()
{
	_buzzerUseCount--;

	if (_buzzerUseCount == 0)
	{
		delete _buzzer;
		_buzzer = nullptr;
	}
}

SevSegms* DeviceManager::requestSevSegms()
{
	_sevSegmsUseCount++;

	if (_sevSegms == nullptr)
		_sevSegms = new SevSegms();

	return _sevSegms;
}

void DeviceManager::releaseSevSegms()
{
	_sevSegmsUseCount--;

	if (_sevSegmsUseCount == 0)
	{
		delete _sevSegms;
		_sevSegms = nullptr;
	}
}

StepperMotor* DeviceManager::requestDividerMotor(Endstop* dividerEndstop)
{
	_dividerMotorUseCount++;

	if (_dividerMotor == nullptr)
		_dividerMotor = new StepperMotor(6, 3, 8, dividerEndstop);

	return _dividerMotor;
}

void DeviceManager::releaseDividerMotor()
{
	_dividerMotorUseCount--;

	if (_dividerMotorUseCount == 0)
	{
		delete _dividerMotor;
		_dividerMotor = nullptr;
	}
}

DcMotor* DeviceManager::requestTableMotor(Endstop* tableEndstop, Potentiometer* potentiometer)
{
	_tableMotorUseCount++;

	if (_tableMotor == nullptr)
		_tableMotor = new DcMotor(tableEndstop, potentiometer);

	return _tableMotor;
}

void DeviceManager::releaseTableMotor()
{
	_tableMotorUseCount--;

	if (_tableMotorUseCount == 0)
	{
		delete _tableMotor;
		_tableMotor = nullptr;
	}
}

Endstop* DeviceManager::requestDividerEndstop()
{
	_dividerEndstopUseCount++;

	if (_dividerEndstop == nullptr)
		_dividerEndstop = new Endstop(10);

	return _dividerEndstop;
}

void DeviceManager::releaseDividerEndstop()
{
	_dividerEndstopUseCount--;

	if (_dividerEndstopUseCount == 0)
	{
		delete _dividerEndstop;
		_dividerEndstop = nullptr;
	}
}

Endstop* DeviceManager::requestTableEndstop()
{
	_tableEndstopUseCount++;

	if (_tableEndstop == nullptr)
		_tableEndstop = new Endstop(9);

	return _tableEndstop;
}

void DeviceManager::releaseTableEndstop()
{
	_tableEndstopUseCount--;

	if (_tableEndstopUseCount == 0)
	{
		delete _tableEndstop;
		_tableEndstop = nullptr;
	}
}

Relay* DeviceManager::requestRelay()
{
	_relayUseCount++;

	if (_relay == nullptr)
		_relay = new Relay();

	return _relay;
}

void DeviceManager::releaseRelay()
{
	_relayUseCount--;

	if (_relayUseCount == 0)
	{
		delete _relay;
		_relay = nullptr;
	}
}

Potentiometer * DeviceManager::requestTablePotentiometer()
{
	_tablePotentiometerUseCount++;

	if (_tablePotentiometer == nullptr)
		_tablePotentiometer = new Potentiometer();

	return _tablePotentiometer;
}

void DeviceManager::releaseTablePotentiometer()
{
	_tablePotentiometerUseCount--;

	if (_tablePotentiometerUseCount == 0)
	{
		delete _tablePotentiometer;
		_tablePotentiometer = nullptr;
	}
}