#ifndef _PROGRAMSTATE_h
#define _PROGRAMSTATE_h

#include "State.h"

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;
class SevSegms;
class StepperMotor;
class DcMotor;
class Endstop;
class Relay;

class ProgramState : public State
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	SevSegms* _sevSegms;

	StepperMotor* _dividerMotor;
	Endstop* _dividerEndstop;
	DcMotor* _tableMotor;
	Endstop* _tableEndstop;
	Relay* _relay;

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
	//Tells if program process is paused
	bool _paused = false;

	//If the process is ended but before buzzer's melody 
	bool _finalized = false;

public:
	ProgramState(Program* program, byte feathers, byte cycles);
	~ProgramState();

	byte getCurrentFeather() { return _currentFeather; };
	void setCurrentFeather(byte currentFeather) { _currentFeather = currentFeather; };
	byte getFeathersCount() { return _feathersCount; };

	byte getCurrentCycle() { return _currentCycle; };
	void setCurrentCycle(byte currentCycle) { _currentCycle = currentCycle; };
	byte getCyclesCount() { return _cyclesCount; };
	
	int getRotateAngle() { return _rotateAngle; };
	bool isFinished() { return _finished; };
	void finish() { _finished = true; };
	void togglePause() { _paused = !_paused; };
	
	bool canChangeFeather();
	bool getInRotationArea() { return _isEndstopClickExecuted; };
	void setInRotationArea(bool inRotationArea) { _isEndstopClickExecuted = inRotationArea; };
	void setRotatedInCycle(bool rotatedInCycle) { _rotatedInPeriod = rotatedInCycle; };

	virtual void react();
};

#endif

