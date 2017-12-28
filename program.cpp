#include "program.h"

Program::Program()
{

}

Program::~Program()
{

}

void Program::init()
{
 
}

void Program::step()
{
	elementManager.getCurrent()->react(input);
	output->display(elementManager.getCurrent());
}

