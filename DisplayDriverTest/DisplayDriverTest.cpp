#include "DisplayDriverTest.h"
#include "Buffer.h"

// Set LED display parameters
const int WD_PX = 20;
const int HT_PX = 10;
const int WD_BYTES = (WD_PX + 7) / 8;
const int BUFF_LEN = WD_BYTES * HT_PX;

// Create LED display object
uint8_t rawDispBuff[BUFF_LEN];
Led::Buffer dispBuff(WD_PX, HT_PX, WD_BYTES, rawDispBuff);

// Prototypes
void test_Buffer_get8Bit();
void test_Buffer_set8Bit();
void test_Buffer_setBit_getBit();

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	test_Buffer_get8Bit();
	//test_Buffer_set8Bit();
	//test_Buffer_setBit_getBit();
}

void test_Buffer_get8Bit()
{
	// Set buffer to all-zeros
	dispBuff.clear(false);

	// Fill the buffer with known data (externally)
	for (int b = 0; b < BUFF_LEN; b++)
		rawDispBuff[b] = b % 255;

	// Loop over byte-alignment
	for (int bAlign = 0; bAlign < 8; bAlign++){

		// Print out the buffer result
		Serial.println("");
		dispBuff.printSerial('X', '.');

		// Loop over the height
		for (int h = 0; h < 3/*dispBuff.getHeight()*/; h++) {

			// Loop across the bytes
			for (int w = bAlign; w < dispBuff.getWidth(); w += 8) {

				// Print current parameters
				String outString = "Set x:" + String(w) + ", y: " + String(h) + ", byteAlign: " + String(bAlign);
				Serial.println(outString);

				// Print the value from the buffer
				uint8_t result = dispBuff.get8Bit(w, h);
				Serial.println(result, BIN);

				// Delay between iterations
				delay(1000);
			}
		}
	}


}

void test_Buffer_set8Bit()
{
	// Set buffer to all-ones
	dispBuff.clear(true);

	// Loop over byte-alignment
	for (int bAlign = 0; bAlign < 8; bAlign++){

		// Loop over the height
		for (int h = 0; h < dispBuff.getHeight(); h++) {

			// Loop across the bytes
			for (int w = bAlign; w < dispBuff.getWidth(); w += 8) {

				// Print current parameters
				String outString = "Set x:" + String(w) + ", y: " + String(h) + ", byteAlign: " + String(bAlign);
				Serial.println(outString);

				// Modify the buffer
				dispBuff.set8Bit(w, h, 0x91);

				// Print out the buffer
				dispBuff.printSerial('X', '.');
				Serial.println("");

				// Delay between iterations
				delay(1000);
			}
		}
	}
}

void test_Buffer_setBit_getBit()
{
	bool writeVal(true);

	while (true)
	{
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
