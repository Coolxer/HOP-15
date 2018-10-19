#pragma once

#include <Arduino.h>
#include "State.h"

class Lcd;
class SimpleKeypad;
class Buzzer;

class SetValueElement;

class ProcessCreatorState : public State
{
private:
	Lcd * _lcd;
	SimpleKeypad* _simpleKeypad;
	Buzzer* _buzzer;

	SetValueElement* _featherAmountElement;
	SetValueElement* _diameterElement;
	SetValueElement* _cutterAngleElement;

	enum Level
	{
		REVIEW,
		FEATHERS_SET,
		DIAMETER_SET,
		ANGLE_SET
	};


	/* LEVELS:
	0 = REVIEW
	1 = FEATHERS_SET
	2 = DIAMETER_SET
	3 = ANGLE_SET	
	*/

	byte _currentLevel = 0;

	float _lastValue;

	bool _changedState = true;

	//Level _currentLevel = REVIEW;

	void startProgram();
public:
	ProcessCreatorState() {};

	virtual void init();
	virtual void react();
	virtual void reset();

	void setFeatherAmountElement(SetValueElement* featherAmountElement) { _featherAmountElement = featherAmountElement; };
	void setDiameterElement(SetValueElement* diameterElement) { _diameterElement = diameterElement; };
	void setCutterAngleElement(SetValueElement* cutterAngleElement) { _cutterAngleElement = cutterAngleElement; };

	byte getFeatherAmount() { return byte(_featherAmountElement->getValue()); };
	float getDiameter() { return _diameterElement->getValue(); };
	float getCutterAngle() { return _cutterAngleElement->getValue(); };

	byte getCurrentLevel() { return _currentLevel; };
};

