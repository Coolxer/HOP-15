#ifndef _PROGRAMELEMENT_h
#define _PROGRAMELEMENT_h

#include "Element.h"

class Lcd;
class SevSegms;
class SimpleKeypad;
class Motor;
class Endstop;

class ProgramElement : public Element
{
private:
	Lcd* _lcd;
	SevSegms* _sevSegms;
	SimpleKeypad* _simpleKeypad;
	Motor* _dividerMotor;
	Endstop* _dividerEndstop;
	Motor* _tableMotor;
	Endstop* _tableEndstop;

	byte _feathers;
	byte _currentFeather;
	byte _cycles;
	byte _currentCycle;
	int _rotateAngle;

	bool _rotatedInCycle = true;
	bool _inRotationArea = false;

	bool _dividerMotorHomed = false;
	bool _tableMotorHomed = false;

	bool _finished = false;

public:
	ProgramElement(char* name, Lcd* lcd, SevSegms* sevSegms, SimpleKeypad* simpleKeypad, Motor* dividerMotor, Endstop* tableEndstop, byte feathers, byte cycles);

	byte getCurrentFeather() { return _currentFeather; };
	void setCurrentFeather(byte currentFeather) { _currentFeather = currentFeather; };
	byte getFeathers() { return _feathers; };

	byte getCurrentCycle() { return _currentCycle; };
	void setCurrentCycle(byte currentCycle) { _currentCycle = currentCycle; };
	byte getCycles() { return _cycles; };
	
	int getRotateAngle() { return _rotateAngle; };
	bool isFinished() { return _finished; };
	void finish() { _finished = true; };
	
	bool canChangeFeather();
	bool getInRotationArea() { return _inRotationArea; };
	void setInRotationArea(bool inRotationArea) { _inRotationArea = inRotationArea; };
	void setRotatedInCycle(bool rotatedInCycle) { _rotatedInCycle = rotatedInCycle; };

	void homeDividerMotor();
	void homeTableMotor();

	virtual void react();
};

#endif

