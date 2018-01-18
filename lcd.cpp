#include "lcd.h"

#include "MenuElement.h"

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

void Lcd::manage(MenuElement* menuElement)
{
	//Line 1
	char* prevName = menuElement->getPrev();
	if (prevName != "")
	{
		writeNewLine(0, "- ");
		writeLine(0, prevName);
		changeLeftOrientation(false);

		char* prevNameValue = menuElement->getPrevValue();
		if (prevNameValue != "")
		{
			writeLine(0, prevNameValue);
			writeLine(0, " /\\");
		}
		else
			writeLine(0, " /\\");
	}
	changeLeftOrientation(true);

	//Line 2
	char* currentName = menuElement->getCurrent();
	if (currentName != "")
	{
		writeNewLine(0, "* ");
		writeLine(0, currentName);
		changeLeftOrientation(false);

		char* currentNameValue = menuElement->getPrevValue();
		if (currentNameValue != "")
		{
			writeLine(0, currentNameValue);
			writeLine(0, " |");
		}
		else
			writeLine(0, " |");
	}
	changeLeftOrientation(true);
	
	//Line 3
	char* nextName = menuElement->getCurrent();
	if (nextName != "")
	{
		writeNewLine(0, "- ");
		writeLine(0, nextName);
		changeLeftOrientation(false);

		char* nextNameValue = menuElement->getPrevValue();
		if (nextNameValue != "")
		{
			writeLine(0, nextNameValue);
			writeLine(0, " \\/");
		}
		else
			writeLine(0, " \\/");
	}
	changeLeftOrientation(true);

	//Line 4
	writeNewLine(3, menuElement->getTip());
}