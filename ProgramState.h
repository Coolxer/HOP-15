#ifndef _PROGRAMSTATE_h
#define _PROGRAMSTATE_h

#include <Arduino.h>
#include "State.h"

class Program;

class Lcd;
class SimpleKeypad;
class Buzzer;
class SevSegms;
class Endstop;
class A4988;
class SyncDriver;
class RotaryEncoder;

enum ExecutionState 
{
	START,
	STARTING,
	MOVE_FORWARD,
	MOVING_FORWARD,
	MOVE_BACKWARD,
	MOVING_BACKWARD,
	CHANGE_FEATHER,
	FINISH,
	PAUSE,
	ENCODER_SERVICE
};

class ProgramState : public State
{
private:
	Lcd* _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;
	SevSegms* _sevSegms;

	Endstop* _forwardTableEndstop;
	Endstop* _backwardTableEndstop;

	A4988* _dividerMotor;
	A4988* _tableMotor;
	SyncDriver* _syncDriver;

	RotaryEncoder* _rotaryEncoder;

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

	//for encoder service
	bool _movingDividerMotorByEncoder = false;
	bool _movingTableMotorByEncoder = false;

	bool _tableMotorHomed = false;

	//Angle of cutter in degrees
	float _cutterAngle = 24.0;

	//Radius of directly motor circle
	float _directlyMotorCircleRadius = 6.0;

	//Radius of shift motor circle
	float _shiftMotorCircleRadius = 12.0;

	//Proportion of divider circle radiuses
	float _proportionOfMotorCircles = 2.0015384;

	float _singleTableMotorStepCount = 16.0;
	float _singleDividerMotorStepCount;

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

	void togglePause();

	bool isPaused();
	bool isFinished();

	void testDividerMotor() { _testingDividerMotor = true; };
	void testTableMotor() { _testingTableMotor = true; };

	void moveDividerMotorByEncoder() { _movingDividerMotorByEncoder = true; };
	void moveTableMotorByEncoder() { _movingTableMotorByEncoder = true; };

	virtual void init();
	virtual void react();
	virtual void reset();
};

#endif

