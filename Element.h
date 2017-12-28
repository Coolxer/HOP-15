#ifndef _ELEMENT_h
#define _ELEMENT_h

class Element
{
private:
	char* name;

public:
	virtual void react(Input* input) = 0;

	void setName(char* name) { this->name = name; };
	char* getName() { return name; };
};

#endif

