#include "program.h"

Program::Program()
{
	input = new SimpleKeypad();
	output = new Lcd();
}

Program::~Program()
{
	delete input;
	delete output;
}

void Program::init()
{
	Element* testElement = new TestElement("Test");

	elementManager.add(testElement);
	elementManager.changeElement("Test");
}

void Program::step()
{
	Element* element = elementManager.getCurrent();

	if (element != nullptr)
	{
		if(element->react(input))
			output->display(element);
	}
}

