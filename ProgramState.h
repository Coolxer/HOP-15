#ifndef _PROGRAMSTATE_h
#define _PROGRAMSTATE_h

#include <Arduino.h>
#include "State.h"

const float PI = 3.1415;

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;
class SevSegms;
class StepperMotor;
class DcMotor;
class Endstop;
class Relay;
class Potentiometer;

enum ExecutionState 
{
	START,
	STARTING,
	MOVE_FORWARD,
	MOVING_FORWARD,
	MOVE_BACKWARD,
	MOVING_BACKWARD,
	UNLOCK_DIVIDER,
	CHANGE_FEATHER,
	LOCK_DIVIDER,
	FINISH,
	PAUSE
};

class ProgramState : public State
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	SevSegms* _sevSegms;

	StepperMotor* _dividerMotor;

	DcMotor* _tableMotor;
	Endstop* _forwardTableEndstop;
	Endstop* _backwardTableEndstop;

	Relay* _relay;
	Potentiometer* _tablePotentiometer;

	//Current state of execution of program
	ExecutionState _currentState = START;

	//Place where last state will be kept on pause
	ExecutionState _savedState;

	int _feathersCount;
	int _currentFeather = 1;

	byte _cyclesCount;
	byte _currentCycle = 1;

	//360 divided by feather count
	float _rotateAngle;

	//Check if motor is between endstops
	bool betweenEndstops;
	//Flag if forward endstop clicked
	bool forwardEndstopClicked;
	//Flag if backward endstop clicked
	bool backwardEndstopClicked;

	bool _testingDividerMotor = false;
	bool _testingTableMotor = false;

	bool _relayHomed = false;
	bool _tableMotorHomed = false;

	//Temporary to measure time interval between table motor move from start to end
	unsigned long _startMillis = 0;
	unsigned long _endMillis = 0;

	//Table motor average speed in meters per second m/s
	float _tableMotorAvgSpeed = 0.1;

	//Angle of cutter in degrees
	float _cutterAngle = 24.0;

	//Radius of directly motor circle
	float _directlyMotorCircleRadius = 6.0;

	//Radius of shift motor circle
	float _shiftMotorCircleRadius = 12.0;

	//Tick time for motor move in ms
	int _tickTime = 10;

	//Proportion of divider circle radiuses
	float _proportionOfMotorCircles;

	//Angle of which divider need to rotate to fit table motor on one tick
	float _degreesToCoverLength;

public:
	void setFeathers(int feathers) { _feathersCount = feathers; };
	void setCycles(byte cycles) { _cyclesCount = cycles; };

	byte getCurrentFeather() { return _currentFeather; };
	void setCurrentFeather(int currentFeather) { _currentFeather = currentFeather; };
	byte getFeathersCount() { return _feathersCount; };

	byte getCurrentCycle() { return _currentCycle; };
	void setCurrentCycle(byte currentCycle) { _currentCycle = currentCycle; };
	byte getCyclesCount() { return _cyclesCount; };
	
	float getRotateAngle() { return _rotateAngle; };

	unsigned long getDeltaTime() { return _endMillis - _startMillis; };

	void togglePause();

	bool isPaused();
	bool isFinished();

	void testDividerMotor() { _testingDividerMotor = true; };
	void testTableMotor() { _testingTableMotor = true; };

	virtual void init();
	virtual void react();
	virtual void reset();
};

#endif

