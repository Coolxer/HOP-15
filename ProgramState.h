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
class MultiDriver;

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
	PAUSE
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
	MultiDriver* _multiDriver;

	//Current state of execution of program
	ExecutionState _currentState = START;

	//Place where last state will be kept on pause
	ExecutionState _savedState;

	byte _feathersCount;
	byte _currentFeather = 1;

	byte _cyclesCount;
	byte _currentCycle = 1;

	float const _PI = 3.1415;

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
	bool _testingHome = false;

	bool _tableMotorHomed = false;

	//Angle of cutter in degrees
	//float _cutterAngle = 24.0;
	float _cutterAngle;

	//Radius of directly motor circle
	float _directlyMotorCircleRadius = 6.0;

	//Radius of shift motor circle
	float _shiftMotorCircleRadius = 12.0;

	//Proportion of divider circle radiuses
	float _proportionOfDividerMotorCircles = 4.0064655;
	float _proportionOfTableMotorCircles = 5.7272727;

	int _singleTableMotorStepCount = 1600;
	int _singleDividerMotorStepCount;

	int NWD(int a, int b);
	int NWW(int a, int b);

	void synchronizedMove(int x);

public:
	void setFeathers(byte feathers) { _feathersCount = feathers; };
	void setCycles(byte cycles) { _cyclesCount = cycles; };
	void setCutterAngle(float angle);

	byte getCurrentFeather() { return _currentFeather; };
	void setCurrentFeather(byte currentFeather) { _currentFeather = currentFeather; };
	byte getFeathersCount() { return _feathersCount; };

	byte getCurrentCycle() { return _currentCycle; };
	void setCurrentCycle(byte currentCycle) { _currentCycle = currentCycle; };
	byte getCyclesCount() { return _cyclesCount; };
	
	float getRotateAngle() { return _rotateAngle; };

	void togglePause();

	bool isPaused();
	bool isFinished();
	bool isHomed() { return _tableMotorHomed; };

	void testDividerMotor() { _testingDividerMotor = true; };
	void testTableMotor() { _testingTableMotor = true; };
	void testHome() { _testingHome = true; };

	virtual void init();
	virtual void react();
	virtual void reset();
};

#endif

