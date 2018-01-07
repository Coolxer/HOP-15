#ifndef _TESTELEMENT_h
#define _TESTELEMENT_h

#include "Element.h"

class TestElement : public Element
{
private:
	char* message = "Congrats!";

public:
	TestElement(char* name) : Element(name) {};
    ~TestElement() {};

	virtual void react();
	char* getMessage() { return message; };
};

#endif

