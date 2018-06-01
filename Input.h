#ifndef _input_h
#define _input_h

#include "Config.h"

class Input
{
public:
	virtual Keys getPressedKey() = 0;
};

#endif

