#include "program.h"

Program::Program()
{

}

Program::~Program()
{

}

void Program::init()
{
	Element* testElement = new TestElement("Test");

	elementManager.add(testElement);
	elementManager.changeElement("Test");
}

void Program::step()
{
	elementManager.getCurrent()->react();
}

