#include "Program.h"

void onProgramStart(MenuElement* menuElement)
{
	ProgramElement* programElement = new ProgramElement("Program", menuElement->_lcd, menuElement->_simpleKeypad, menuElement->_buzzer, menuElement->_sevSegms,  menuElement->_dividerMotor, menuElement->_tableMotor, menuElement->_dividerEndstop, menuElement->_tableEndstop, menuElement->_relay, menuElement->getValueAtIndex(0), menuElement->getValueAtIndex(1));
	menuElement->getElementManager()->add(programElement);
	menuElement->getElementManager()->changeElement("Program");
}

void Program::init()
{
	IntroductionElement* introductionElement = new IntroductionElement("intro", &_lcd, &_simpleKeypad, &_buzzer);

	SetValueElement* featherAmount = new SetValueElement("Piora", &_lcd, &_simpleKeypad, 2, 32, 4, 2);
	SetValueElement* cycleAmount = new SetValueElement("Cykle", &_lcd, &_simpleKeypad, 1, 16, 1, 1);

	MenuElement* menuElement = new MenuElement("mainMenu", &_lcd, &_simpleKeypad, &_buzzer, &_sevSegms, _dividerMotor, _tableMotor, _dividerEndstop, _tableEndstop, _relay, 3);

	menuElement->setElement(0, featherAmount);
	menuElement->setElement(1, cycleAmount);
	menuElement->setElement(2, "Rozpocznij", &onProgramStart);

	_stateManager.add(introductionElement);
	_stateManager.add(menuElement);
	_stateManager.changeElement("intro");
}

void Program::step()
{
	_stateManager.getCurrent()->react();
}

