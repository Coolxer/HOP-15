#include "Lcd.h"

#include "IntroductionState.h"
#include "MenuState.h"
#include "ProgramState.h"

Lcd::Lcd()
{
	_lcd.begin(20, 4);
}

void Lcd::clearLine(byte lineNumber)
{
	for (byte i = 0; i < _cols; i++)
	{
		_lcd.setCursor(i, lineNumber);
		_lcd.print(' ');
	}

	resetPointers(lineNumber);
}

void Lcd::resetPointers(byte lineNumber)
{
	_linesPointers[lineNumber].leftPointer = 0;
	_linesPointers[lineNumber].rightPointer = _cols - 1;
}

void Lcd::clearScreen()
{
	_lcd.clear();
}

void Lcd::writeLine(byte lineNumber, char* text)
{
	if (_textToLeft)
	{
		byte leftPointer = _linesPointers[lineNumber].leftPointer;

		_lcd.setCursor(leftPointer, lineNumber);
		_lcd.print(text);
		_linesPointers[lineNumber].leftPointer = leftPointer + strlen(text);
	}
	else
	{
		byte rightPointer = _linesPointers[lineNumber].rightPointer - strlen(text);

		_lcd.setCursor(rightPointer, lineNumber);
		_lcd.print(text);
		_linesPointers[lineNumber].rightPointer = rightPointer;
	}
}

void Lcd::writeNewLine(byte lineNumber, char* text)
{
	clearLine(lineNumber);
	writeLine(lineNumber, text);
}

void Lcd::manage(MenuState* menuState)
{
	//Line 1
	char* prevName = (char*)menuState->getPrev();

	if (prevName != "")
	{
		writeNewLine(0, "- ");
		writeLine(0, prevName);
		changeLeftOrientation(false);

		char* prevNameValue = (char*)menuState->getPrevValue();
		if (prevNameValue != "")
		{
			writeLine(0, "^");
			writeLine(0, prevNameValue);
		}
		else
			writeLine(0, "^");
	}
	changeLeftOrientation(true);

	//Line 2
	char* currentName = (char*)menuState->getCurrent();
	if (currentName != "")
	{
		writeNewLine(1, "* ");
		writeLine(1, currentName);
		changeLeftOrientation(false);

		char* currentNameValue = (char*)menuState->getCurrentValue();
		if (currentNameValue != "")
		{
			writeLine(1, "I");
			writeLine(1, currentNameValue);
		}
		else
			writeLine(1, "I");
	}
	changeLeftOrientation(true);
	
	//Line 3
	char* nextName = (char*)menuState->getNext();
	if (nextName != "")
	{
		writeNewLine(2, "- ");
		writeLine(2, nextName);
		changeLeftOrientation(false);

		char* nextNameValue = (char*)menuState->getNextValue();
		if (nextNameValue != "")
		{
			writeLine(2, "V");
			writeLine(2, nextNameValue);
		}                                          
		else
			writeLine(2, "V");
	}
	changeLeftOrientation(true);

	//Line 4
	writeNewLine(3, menuState->getTip());
}

void Lcd::manage(IntroductionState* introductionState)
{
	writeNewLine(0, introductionState->getCompanyName());
	writeNewLine(1, introductionState->getProgramName());
	writeNewLine(2, introductionState->getMachineAuthor());
	writeNewLine(3, introductionState->getInfo());
}

void Lcd::manage(ProgramState* programState)
{
	if (programState->isFinished())
	{
		clearScreen();
		writeNewLine(0, "Zakonczono");
		writeNewLine(3, "* by wrocic do menu");
	}
	else
	{
		writeNewLine(0, "Przetwarzanie w toku");

		byte feather = programState->getCurrentFeather();
		byte feathers = programState->getFeathersCount();
		byte cycle = programState->getCurrentCycle();
		byte cycles = programState->getCyclesCount();

		char featherLine[20] = { 0 };
		char cycleLine[20] = { 0 };

		sprintf(featherLine, "Pioro nr %d z %d", feather, feathers);
		sprintf(cycleLine, "Cykl nr %d z %d", cycle, cycles);

		writeNewLine(1, featherLine);
		writeNewLine(2, cycleLine);

		if(programState->isPaused())
			writeNewLine(3, "*-Wznów #-Zatrzymaj");
		else
			writeNewLine(3, "*-Pauza #-Zatrzymaj");
	}
}