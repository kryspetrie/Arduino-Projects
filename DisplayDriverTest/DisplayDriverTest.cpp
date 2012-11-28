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
void test_Buffer_setBit_getBit();

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	test_Buffer_setBit_getBit();
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
