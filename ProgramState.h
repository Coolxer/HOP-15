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

enum ExecutionState 
{
	START,
	MOVE_FORWARD,
	MOVING_FORWARD,
	MOVE_BACKWARD,
	MOVING_BACKWARD,
	CHANGE_FEATHER,
	FINISH,
	PAUSE,
	REGULATION
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

	//Current state of execution of program
	ExecutionState _currentState = START;

	//Place where last state will be kept on pause
	ExecutionState _savedState;

	byte _feathersCount;
	byte _currentFeather = 1;

	byte _cyclesCount;
	byte _currentCycle = 1;

	//360 divided by feather count
	float _rotateAngle;

	//How many steps should motor move to change feather
	double _stepsForFeather;

	//Check if motor is between endstops
	bool betweenEndstops;
	//Flag if forward endstop clicked
	bool forwardEndstopClicked;
	//Flag if backward endstop clicked
	bool backwardEndstopClicked;

	bool _testingDividerMotor = false;
	bool _testingTableMotor = false;
	bool _testingHome = false;
	bool _regulation = false;

	bool _tableMotorHomed = false;

	bool _turningRight = true;

	//after finish we need to get back to the first feather, this bool is setted to
											//true after this operation
	bool ended = false;

	//Angle of cutter in degrees
	double _cutterAngle;

	//Diameter of cutter
	double _diameter;

	double _tableSpeed;
	double _dividerSpeed;

	unsigned long _tableStepInterval;
	unsigned long _dividerStepInterval;

	//delay between motors movements in ms
	int _delay = 100;

	void calcSteps();

	void home();
	void changeFeather();

public:
	void setFeathers(byte feathers) { _feathersCount = feathers; };
	void setCycles(byte cycles) { _cyclesCount = cycles; };
	//void setCutterAngle(double angle) { _cutterAngle = angle; };
	void setCutterAngle(double cutterAngle) { _cutterAngle = cutterAngle; };
	void setDiameter(double diameter) { _diameter = diameter; };
	void setSpeed(int speed) { _tableSpeed = speed; };

	byte getCurrentFeather() { return _currentFeather; };
	void setCurrentFeather(byte currentFeather) { _currentFeather = currentFeather; };
	byte getFeathersCount() { return _feathersCount; };

	byte getCurrentCycle() { return _currentCycle; };
	void setCurrentCycle(byte currentCycle) { _currentCycle = currentCycle; };
	byte getCyclesCount() { return _cyclesCount; };

	double getCutterAngle() { return _cutterAngle; };

	bool isPaused();
	bool isFinished();
	bool isHomed() { return _tableMotorHomed; };
	bool isEnded() { return ended; };

	bool getDirection() { return _turningRight; };
	void setDirection(bool x) { _turningRight = x; };

	void testDividerMotor() { _testingDividerMotor = true; };
	void testTableMotor() { _testingTableMotor = true; };
	void testHome() { _testingHome = true; };

	virtual void init();
	virtual void react();
	virtual void reset();

	void setRegulation() { _regulation = true; };
};

#endif

