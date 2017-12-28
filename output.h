#ifndef _output_h
#define _output_h

#include "TestElement.h"

class Output
{
public:
	virtual void display(Element* element) = 0;
};

#endif

