#include "DisplayDriverTest.h"
#include "Buffer.h"
#include "SimpleFont.h"

using namespace Display;

// Set LED display parameters
const int WD_PX = 100; //20;
const int HT_PX = 10;
const int WD_BYTES = (WD_PX + 7) / 8;
const int BUFF_LEN = WD_BYTES * HT_PX;

// Create LED display object
uint8_t rawDispBuff[BUFF_LEN];
Buffer dispBuff(WD_PX, HT_PX, WD_BYTES, rawDispBuff);
SimpleFont sFont(&dispBuff);

void test_StructUnion() {
	// http://stackoverflow.com/questions/12940211/arrays-unions-structs-containing-bit-fields-c

	// define union
	typedef union {
		uint8_t raw;

		struct {
			byte red : 3;
			byte green : 3;
			byte blue : 2;
		};
	} Pixel;

	// define array
	static const int cArrLen(5);
	Pixel pixArray[cArrLen];

	// clear array
	for (int i = 0; i < cArrLen; i++)
		pixArray[i].raw = 0x0;

	// Set the first pixel (will truncate)
	pixArray[0].red = 0xFF;
	pixArray[0].green = 0xFF;
	pixArray[0].blue = 0xFF;

	// Print out what was set;
	Serial.println("red: " + String(pixArray[0].red, BIN));
	Serial.println("green: " + String(pixArray[0].green, BIN));
	Serial.println("blue: " + String(pixArray[0].blue, BIN));

	while(1);
}


void setup() {
	Serial.begin(9600);
}

void loop() {
	test_StructUnion();
}

#ifdef TESTCODE

void test_SimpleFont_writeString_2() {
	Color colorA(BLACK);
	Color colorB(WHITE);
	sFont.setColor(colorB);

	for (int yInd = -6; yInd < 11; yInd++) {
		dispBuff.clear(colorA);
		sFont.drawString(1, yInd, "ABC-123-/|\\");
		dispBuff.printSerial('@', '.');
		Serial.println("");

		delay(750);
	}
}

void test_SimpleFont_writeString() {
	Color colorA(BLACK);
	Color colorB(WHITE);

	while (true) {
		dispBuff.clear(colorA);
		sFont.setColor(colorB);
		sFont.drawString(0, 0, "ASDF_string");
		sFont.drawString(0, 5, "Lolol@#$%&");
		dispBuff.printSerial('@', '.');

		// swap colors
		Color tmp(colorA);
		colorA = colorB;
		colorB = tmp;

		delay(1000);
	}
}

void test_SimpleFont_writeChar_all() {
	sFont.setColor(WHITE);
	sFont.setStyle(NOSTYLE);

	while (true) {
		for (char c = ' '; c < '~'; c++) {

			dispBuff.clear(BLACK);
			sFont.drawChar(1, 1, c);
			Serial.println("Current Character: " + String(c) + ", Val: " + String((int) c, DEC));
			dispBuff.printSerial('#', '-');
			Serial.println("");
			delay(100);
		}

		if (sFont.getStyle() == NOSTYLE)
		sFont.setStyle(BOLD);
		else
		sFont.setStyle(NOSTYLE);
	}
}

void test_SimpleFont_writeChar() {

	Color a(BLACK);
	Color b(WHITE);

	while (true) {

		dispBuff.clear(a);
		sFont.setColor(b);
		sFont.drawChar(1, 1, '9');
		sFont.drawChar(6, 1, '2');
		sFont.drawChar(11, 1, '5');
		dispBuff.printSerial('#', '-');
		delay(5000);

		// Swap colors
		Color tmp(a);
		a = b;
		b = tmp;
	}
}

void test_Buffer_fastHLine_2() {

	bool color(true);

	while (true) {

		dispBuff.clearRaw(!color);
		Serial.println("Color: " + String(color));

		dispBuff.clearRaw(!color);
		dispBuff.fastHLine(0, 0, 19, color);
		dispBuff.fastHLine(0, 1, 20, color);
		dispBuff.fastHLine(0, 2, 21, color);
		dispBuff.fastHLine(1, 3, 19, color);
		dispBuff.fastHLine(1, 4, 20, color);
		dispBuff.fastHLine(1, 5, 21, color);
		dispBuff.printSerial('1', '0');
		Serial.println("");

		color = !color;
		delay(5000);
	}
}

void test_Buffer_fastHLine() {

	bool color(true);

	while (true) {

		dispBuff.clearRaw(!color);
		Serial.println("Color: " + String(color));

		// Draw a bunch of lines
		dispBuff.fastHLine(0, 0, 3, color);
		dispBuff.fastHLine(3, 1, 3, color);
		dispBuff.fastHLine(6, 2, 4, color);
		dispBuff.fastHLine(0, 3, 19, color);
		dispBuff.fastHLine(1, 4, 18, color);

		// Draw Difficult cases
		dispBuff.fastHLine(16, 5, 8, color);
		dispBuff.fastHLine(16, 6, 16, color);
		dispBuff.fastHLine(16, 7, 4, color);

		// Out of bounds
		dispBuff.fastHLine(16, 10, 5, color);
		dispBuff.fastHLine(0, -1, 10, color);
		dispBuff.fastHLine(-4, 8, 11, color);

		// Print buffer
		dispBuff.printSerial('1', '0');
		Serial.println("");

		color = !color;
		delay(5000);
	}
}

void test_Buffer_set8Bit_neg() {
	dispBuff.clear(false);

	// test some key values
	dispBuff.set8Bit(0, -1, 0xFF);
	dispBuff.set8Bit(0, dispBuff.getHeight() + 1, 0xFF);
	dispBuff.set8Bit(-8, 0, 0xFF);
	dispBuff.set8Bit(-7, 1, 0xFF);
	dispBuff.set8Bit(-3, 2, 0xFF);
	dispBuff.set8Bit(-1, 3, 0XFF);

	dispBuff.printSerial('1', '0');
	Serial.println("");
	delay(5000);
}

void test_Buffer_get8Bit_neg() {

	// Clear the buffer with 1's
	dispBuff.clear(true);

	// test some key values
	uint8_t rowNeg1 = dispBuff.get8Bit(0, -1);
	uint8_t rowPastLast = dispBuff.get8Bit(0, dispBuff.getHeight() + 1);
	uint8_t neg7row0 = dispBuff.get8Bit(-7, 0);
	uint8_t neg8row0 = dispBuff.get8Bit(-8, 0);
	uint8_t neg7row1 = dispBuff.get8Bit(-7, 1);
	uint8_t neg8row1 = dispBuff.get8Bit(-8, 1);
	uint8_t neg4row5 = dispBuff.get8Bit(-4, 5);

	// Print buffer
	dispBuff.printSerial('1', '0');
	Serial.println("");

	// Print results
	Serial.println(String("row -1: ") + String(rowNeg1, BIN));
	Serial.println(String("last row + 1: ") + String(rowPastLast, BIN));
	Serial.println(String("-7, 0: ") + String(neg7row0, BIN));
	Serial.println(String("-8, 0: ") + String(neg8row0, BIN));
	Serial.println(String("-7, 1: ") + String(neg7row1, BIN));
	Serial.println(String("-8, 1: ") + String(neg8row1, BIN));
	Serial.println(String("-4, 5: ") + String(neg4row5, BIN));
	Serial.println("");

	delay(2000);
}

void test_Buffer_clear() {
	bool clearType(false);

	while (true) {
		// Put some data into the buffer
		for (int b = 0; b < BUFF_LEN; b++)
		dispBuff.setByte(b, 0xAA);

		// Print the buffer
		dispBuff.printSerial('1', '0');
		Serial.println("");

		// Clear the buffer
		dispBuff.clear(clearType);

		// Print the buffer
		dispBuff.printSerial('1', '0');
		Serial.println("");

		// Flip the clear type
		clearType = !clearType;

		delay(1500);
	}
}

void test_Buffer_get8Bit() {
	int subTest(0);

	while (true) {

		// Set buffer to all-zeros
		dispBuff.clear(false);

		// Fill the buffer with known data (externally)
		switch (subTest) {

			case 0:
			// Fill with all-ones
			dispBuff.clear(true);
			break;

			case 1:
			// Fill with 1-0 pattern
			dispBuff.fillRaw(0xAA);
			break;

			case 2:
			// Fill with 0-1 pattern
			dispBuff.fillRaw(0x55);
			break;

			case 3:
			// Fill with numbers
			for (int b = 0; b < dispBuff.getSize(); b++)
			dispBuff.setByte(b, (b % 255));
			break;
		}

		// Loop over byte-alignment
		for (int bAlign = 0; bAlign < 8; bAlign++) {

			// Print out the buffer result
			Serial.println("");
			dispBuff.printSerial('X', '.');

			// Loop over the height
			for (int h = 0; h < dispBuff.getHeight(); h++) {

				// Loop across the bytes
				for (int w = bAlign; w < dispBuff.getWidth(); w += 8) {

					// Get the value from the buffer
					uint8_t result = dispBuff.get8Bit(w, h);

					// Print current parameters
					String outString = "Set x:" + String(w) + ", y: "
					+ String(h) + ", byteAlign: " + String(bAlign)
					+ ", binary: " + String(result, BIN);
					Serial.println(outString);

					// Delay between iterations
					delay(100);
				}
			}
		}

		subTest = (subTest + 1) % 4;
	}

}

void test_Buffer_set8Bit() {

	bool writeVal(true);

	while (true) {

		// Loop over byte-alignment
		for (int bAlign = 0; bAlign < 8; bAlign++) {

			// Loop over the height
			for (int h = 0; h < 1 /*dispBuff.getHeight()*/; h++) {

				// Loop across the bytes
				for (int w = bAlign; w < dispBuff.getWidth(); w += 8) {

					// Set buffer to all-ones
					dispBuff.clear(writeVal);

					// Print current parameters
					String outString = "Set x:" + String(w) + ", y: "
					+ String(h) + ", byteAlign: " + String(bAlign);
					Serial.println(outString);

					// Modify the buffer
					dispBuff.set8Bit(w, h, 0x81);

					// Print out the buffer
					dispBuff.printSerial('X', '.');
					Serial.println("");

					// Delay between iterations
					delay(1000);
				}
			}
		}

		writeVal = !writeVal;
	}
}

void test_Buffer_setBit_getBit() {
	bool writeVal(true);

	while (true) {
		// Loop over the height
		for (int h = 0; h < dispBuff.getHeight(); h++) {

			// Loop across the bits
			for (int w = 0; w < dispBuff.getWidth(); w++) {

				// Print current coord
				Serial.print("Set x: ");
				Serial.print(w);
				Serial.print(", y: ");
				Serial.println(h);

				// Modify the buffer
				dispBuff.setBit(w, h, writeVal);

				// Print out the buffer
				dispBuff.printSerial('X', '.');
				Serial.println("");

				// Delay between iterations
				delay(100);
			}
		}

		// Flip the value to write
		writeVal = !writeVal;
	}
}
#endif
