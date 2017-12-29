#ifndef _output_h
#define _output_h

#include "TestElement.h"

class Output
{
public:
	virtual void display(TestElement* element) = 0;
};

#endif

