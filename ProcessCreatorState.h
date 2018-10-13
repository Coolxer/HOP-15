#pragma once

#include <Arduino.h>
#include "State.h"

class ProcessCreatorState : public State
{
private:

public:
	ProcessCreatorState();
	~ProcessCreatorState();

	virtual void init();
	virtual void react();
	virtual void reset();
};

