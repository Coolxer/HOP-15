#ifndef _STATE_h
#define _STATE_h

class Program;

class State 
{
protected:
	Program* _program;
	bool _needRedraw = true;

public:
	State() {};
	virtual ~State() {};

	virtual void init() = 0;
	virtual void react() = 0;
	virtual void reset() = 0;

	void needRedraw() { _needRedraw = true; };

	Program* getProgram() { return _program; };
	void setProgram(Program* program) { _program = program; };
};


#endif

