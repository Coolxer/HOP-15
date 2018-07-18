#ifndef lcd_h
#define lcd_h

#include "Arduino.h"
#include <LiquidCrystal.h>

class IntroductionState;
class MenuState;
class ProgramState;

struct LinePointerPair
{
	byte leftPointer;
	byte rightPointer;
};

class Lcd
{
private:
	LiquidCrystal _lcd = LiquidCrystal(22, 24, 26, 28, 30, 32);

	byte _cols = 20;
	byte _rows = 4;

	bool _textToLeft = true;

	LinePointerPair _linesPointers[4] = 
	{
		{ 0, 19 },
		{ 0, 19 },
		{ 0, 19 },
		{ 0, 19 }
	};

	void resetPointers(byte lineNumber);

public:
	Lcd();

	void changeLeftOrientation(bool isTextToLeft) { _textToLeft = isTextToLeft; };

	void clearScreen();
	void clearLine(byte lineNumber);
	void writeLine(byte lineNumber, char* text);
	void writeNewLine(byte lineNumber, char* text);

	void manage(MenuState* menuState);
	void manage(IntroductionState* introductionState);
	void manage(ProgramState* programState);
};

#endif


