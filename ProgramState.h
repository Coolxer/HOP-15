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

class AccelStepper;
class MultiStepper;

class SetValueElement;

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

	AccelStepper* _dividerMotor;
	AccelStepper* _tableMotor;
	MultiStepper* _multiStepper;

	SetValueElement* _cutterAngleElement;

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
	double _cutterAngle;
	double _lastCutterAngle;

	//Diameter of cutter
	double _diameter;

	double _smallGearOfDividerMotor = 34.81;
	double _bigGearOfDividerMotor = 130.1;

	double _smallGearOfTableMotor = 16.42;
	double _bigGearOfTableMotor = 87;

	//Proportion of divider circle radiuses
	double _proportionOfDividerMotorCircles;
	double _proportionOfTableMotorCircles;

	double _tableCountInMM = 50;
	double _dividerCountInMM;

	double _tableCountInSteps;
	double _dividerCountInSteps;

	double _tableSpeed;
	double _multiplier;
	double _dividerSpeed;

	void calcSteps();

public:
	void setFeathers(byte feathers) { _feathersCount = feathers; };
	void setCycles(byte cycles) { _cyclesCount = cycles; };
	//void setCutterAngle(double angle) { _cutterAngle = angle; };
	void setCutterAngle(SetValueElement* cutterAngleElement) { _cutterAngleElement = cutterAngleElement; };
	void setDiameter(double diameter) { _diameter = diameter; };
	void setSpeed(double speed) { _tableSpeed = speed; };

	void set();
	byte getCurrentFeather() { return _currentFeather; };
	void setCurrentFeather(byte currentFeather) { _currentFeather = currentFeather; };
	byte getFeathersCount() { return _feathersCount; };

	byte getCurrentCycle() { return _currentCycle; };
	void setCurrentCycle(byte currentCycle) { _currentCycle = currentCycle; };
	byte getCyclesCount() { return _cyclesCount; };

	double getCutterAngle() { return _cutterAngle; };

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

