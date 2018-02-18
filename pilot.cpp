#include "pilot.h"

Pilot::Pilot()
{
	//_irrecv = new IRrecv(_irPin);
}

Pilot::~Pilot()
{
	//delete _irrecv;
}

/* PILOT OVERVIEW */

/*
-------------------- -
| CH- | CH | CH+ |
-------------------- -
| << | >> | >= |
-------------------- -
| - | + | EQ |
-------------------- -
| 0 | FL- | FL+ |
-------------------- -
| 1 | 2 | 3 |
-------------------- -
| 4 | 5 | 6 |
-------------------- -
| 7 | 8 | 9 |
-------------------- -
*/

void Pilot::listening()
{
	/*
	if (_irrecv->decode(&_results))
	{
		switch (_results.value)
		{
		case 0xFFA25D:
			Serial.println("CH-");
			break;

		case 0xFF629D:
			Serial.println("CH");
			break;

		case 0xFFE21D:
			Serial.println("CH+");
			break;

		case 0xFF22DD:
			Serial.println("<<");
			break;

			// >> this not working //
			//>|| tthis not working //

		case 0xFFE01F:
			Serial.println("-");
			break;

		case 0xFFA857:
			Serial.println("+");
			break;

		case 0xFF906F:
			Serial.println("EQ");
			break;

		case 0xFF6897:
			Serial.println("0");
			break;

		case 0xFF9867:
			Serial.println("FOL-");
			break;

		case 0xFFB04F:
			Serial.println("FOL+");
			break;

		case 0xFF30CF:
			Serial.println("1");
			break;

		case 0xFF18E7:
			Serial.println("2");
			break;

		case 0xFF7A85:
			Serial.println("3");
			break;

		case 0xFF10EF:
			Serial.println("4");
			break;

		case 0xFF38C7:
			Serial.println("5");
			break;

		case 0xFF5AA5:
			Serial.println("6");
			break;

			// 7 is not working //

		case 0xFF4AB5:
			Serial.println("8");
			break;

		case 0xFF52AD:
			Serial.println("9");
			break;

		}
		_irrecv->resume();
	}
	*/
}
