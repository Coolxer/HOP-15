#ifndef _STATE_h
#define _STATE_h

class Program;

class State 
{
protected:
	Program* _program;
	bool _needRedraw = true;
	//If there was any physical disruptions
	bool _disrupted = false;

public:
	State() {};
	virtual ~State() {};

	virtual void init() = 0;
	virtual void react() = 0;
	virtual void reset() = 0;

	void needRedraw() { _needRedraw = true; };
	void reportDisruption() { _disrupted = true; }
	void(*resetFunc) (void) = 0;

	Program* getProgram() { return _program; };
	void setProgram(Program* program) { _program = program; };
};


#endif

