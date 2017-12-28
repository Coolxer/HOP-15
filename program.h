#ifndef program_h
#define program_h

#include "input.h"
#include "output.h"

#include "ElementManager.h"
#include "TestElement.h"

class Program
{
private:
	Output* output;
	Input* input;

	ElementManager elementManager;

public:
	Program();
	~Program();
  
    void init();
    void step();
};

#endif
