#ifndef lcd_h
#define lcd_h

#include <LiquidCrystal.h>
#include "output.h"

struct LinePointerPair
{
	byte leftPointer;
	byte rightPointer;
};

class Lcd : public Output
{
private:
	LiquidCrystal _lcd = LiquidCrystal(40, 42, 44, 46, 48, 50);

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

};

#endif


