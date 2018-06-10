#ifndef _STATE_h
#define _STATE_h

class Program;

class State 
{
protected:
	Program* _program;
	bool _needRedraw = true;

public:
	State(Program* program) { _program = program; };
	virtual ~State() {};

	virtual void react() = 0;

	void needRedraw() { _needRedraw = true; };

	Program* getProgram() { return _program; };
};


#endif

