#ifndef _PROGRAMELEMENT_h
#define _PROGRAMELEMENT_h

#include "Element.h"

class Lcd;
class SimpleKeypad;
class Buzzer;
class SevSegms;
class StepperMotor;
class Endstop;

class ProgramElement : public Element
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	SevSegms* _sevSegms;

	StepperMotor* _dividerMotor;
	Endstop* _dividerEndstop;
	StepperMotor* _tableMotor;
	Endstop* _tableEndstop;

	byte _feathersCount;
	byte _currentFeather;

	byte _cyclesCount;
	byte _currentCycle;

	//360 divided by feather count
	byte _rotateAngle;

	bool _rotatedInPeriod = true;
	bool _isEndstopClickExecuted = false;
	bool _isMotorMoveForward = true;
	byte _motorAngleRotateSpeed = 5;

	bool _dividerMotorHomed = false;
	bool _tableMotorHomed = false;

	//If all two motors are homed initiation is finished and set to true
	bool _inited = false;
	//If all cycles and feathers in cycle was processed this flag is set to true
	bool _finished = false;

	//If the process is ended but before buzzer's melody 
	bool _finalized = false;

public:
	ProgramElement(char* name, Lcd* lcd, SimpleKeypad* simpleKeypad, Buzzer* buzzer, SevSegms* sevSegms, StepperMotor* dividerMotor, StepperMotor* tableMotor, Endstop* dividerEndstop, Endstop* tableEndstop, byte feathers, byte cycles);

	byte getCurrentFeather() { return _currentFeather; };
	void setCurrentFeather(byte currentFeather) { _currentFeather = currentFeather; };
	byte getFeathersCount() { return _feathersCount; };

	byte getCurrentCycle() { return _currentCycle; };
	void setCurrentCycle(byte currentCycle) { _currentCycle = currentCycle; };
	byte getCyclesCount() { return _cyclesCount; };
	
	int getRotateAngle() { return _rotateAngle; };
	bool isFinished() { return _finished; };
	void finish() { _finished = true; };
	
	bool canChangeFeather();
	bool getInRotationArea() { return _isEndstopClickExecuted; };
	void setInRotationArea(bool inRotationArea) { _isEndstopClickExecuted = inRotationArea; };
	void setRotatedInCycle(bool rotatedInCycle) { _rotatedInPeriod = rotatedInCycle; };

	void homeDividerMotor();
	void homeTableMotor();

	virtual void react();
};

#endif

