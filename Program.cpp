#include "Program.h"

Program::Program()
{
	_dividerEndstop = new Endstop(10);
	_tableEndstop = new Endstop(9);

	_dividerMotor = new StepperMotor(6, 3, 8, _dividerEndstop);
	_tableMotor = new StepperMotor(5, 2, 8, _tableEndstop);
}

Program::~Program()
{
	delete _dividerMotor;
	delete _tableMotor;
	delete _dividerEndstop;
	delete _tableEndstop;
}

void onProgramStart(MenuElement* menuElement)
{
	ProgramElement* programElement = new ProgramElement("Program", menuElement->_lcd, menuElement->_simpleKeypad, menuElement->_buzzer, menuElement->_sevSegms,  menuElement->_dividerMotor, menuElement->_tableMotor, menuElement->_dividerEndstop, menuElement->_tableEndstop, menuElement->getValueAtIndex(0), menuElement->getValueAtIndex(1));
	menuElement->getElementManager()->add(programElement);
	menuElement->getElementManager()->changeElement("Program");
}

void Program::init()
{
	IntroductionElement* introductionElement = new IntroductionElement("intro", &_lcd, &_simpleKeypad, &_buzzer);

	SetValueElement* featherAmount = new SetValueElement("Piora", &_lcd, &_simpleKeypad, 2, 32, 4, 2);
	SetValueElement* cycleAmount = new SetValueElement("Cykle", &_lcd, &_simpleKeypad, 1, 16, 1, 1);

	MenuElement* menuElement = new MenuElement("mainMenu", &_lcd, &_simpleKeypad, &_buzzer, &_sevSegms, _dividerMotor, _tableMotor, _dividerEndstop, _tableEndstop, 3);

	menuElement->setElement(0, featherAmount);
	menuElement->setElement(1, cycleAmount);
	menuElement->setElement(2, "Rozpocznij", &onProgramStart);

	_elementManager.add(introductionElement);
	_elementManager.add(menuElement);
	_elementManager.changeElement("intro");
}

void Program::step()
{
	_elementManager.getCurrent()->react();
}

