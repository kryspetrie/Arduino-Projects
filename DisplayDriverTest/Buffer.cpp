/*
 * Buffer.cpp
 *
 *  Created on: Dec 13, 2012
 *      Author: cpetrie
 */

#include "Buffer.h"

namespace Display {

/**
 * Prints out the buffer to the serial port.  Note that the
 *  serial port must be opened before using this function.
 */
void Buffer::_printSerial(char ones, char zeros) {
	int height = getHeight();
	int width = getWidth();

	// Loop over the height
	for (int h = 0; h < height; h++) {

		// Loop across the bits
		for (int w = 0; w < width; w++) {

			// Get the bit
			Color color = getBit(w, h);

			// Print the bit
			char bitChar = (color == WHITE) ? ones : zeros;
			Serial.print(bitChar);
		}

		// Print an end-line for each row
		Serial.println("");
	}
}

} /* namespace Display */
