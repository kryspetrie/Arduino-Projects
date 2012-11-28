/*
 * Buffer.cpp
 *
 *  Created on: Nov 25, 2012
 *      Author: cpetrie
 */

#include "Buffer.h"
using namespace Led;

/**
 * Creates a buffer object with a certain width/height, using the
 *  provided buffer.  The provided buffer MUST BE equal to at least
 *  pitchBytes * height.
 *
 *  @param width The width of the image buffer in pixels
 *  @param height The height of image buffer in pixels
 *  @param pitchBytes The number of bytes provided for each row.
 *  	This must be at least floor( (width + 7)/8 ) bytes
 *  @param buff pointer to the display buffer array
 */
Buffer::Buffer(const int width, const int height, const int pitchBytes, uint8_t* buff) :
		_width(width), _height(height), _pitchBytes(pitchBytes), _buff(buff) {
	clear();
}

void Buffer::clear(bool val) {
	uint8_t bits = val ? 0xFF : 0x00;
	memset(_buff, bits, sizeof(uint8_t));
}

/**
 * Prints out the buffer to the serial port.  Note that the
 *  serial port must be opened before using this function.
 */
void Buffer::printSerial(char ones, char zeros) {

	// Loop over the height
	for (int h = 0; h < _height; h++) {

		// Loop across the bits
		for (int w = 0; w < _width; w++) {

			// Get the bit
			bool bit = getBit(w, h);

			// Print the bit
			char bitChar = bit ? ones : zeros;
			Serial.print(bitChar);

		}

		// Print an end-line for each row
		Serial.println("");
	}
}

void Buffer::setBit(int x, int y, bool val) {

	// Check input variables
	if (x > _width || y > _height)
		return;

	// Get byte pointer that contains the bit
	uint8_t* bitBytePtr = _buff + (_pitchBytes * y) + x/8;

	// Shift over the bit to change
	uint8_t bit = 0x01 << (7 - (x % 8));

	if (val) {
		*bitBytePtr |= bit;  // set the bit
	} else {
		*bitBytePtr &= ~bit; // clear the bit
	}
}

bool Buffer::getBit(int x, int y) {

	// Check input variables
		if (x > _width || y > _height)
			return false;

	// Get byte that contains the bit
	uint8_t bitByte = *(_buff + (_pitchBytes * y) + x/8);

	// Shift the byte to extract the desired bit
	uint8_t bit = (bitByte << (x % 8)) & 0x80;

	return bit ? true : false;
}

void Buffer::set8Bit(int x, int y, uint8_t data, BlendMode m) {
	// TODO implement!

	// Get byte pointer that contains the leftmost bit
	uint8_t* bitBytePtr = _buff + (_pitchBytes * y) + x/8;



}

uint8_t Buffer::get8Bit(int x, int y) {

	// Get byte that contains the most significant part of the 8-bits
	uint8_t* bitsByte1 = _buff + (_pitchBytes * y) + x/8;

	// Get the width remainder
	uint8_t rem = (x % 8);

	// Shift the byte to extract the desired bits
	uint8_t bits = (*bitsByte1 << rem);

	// Mask out bits beyond width of display
	// TODO

	// If we data from the following byte as well
	if (rem != 0 && (x/8 < _pitchBytes)) {

		// Get byte that contains the least significant part of the 8 bits
		uint8_t* bitsByte2 = bitsByte1++;

		// Shift the byte to extract the desired bits
		bits |= (*bitsByte2 >> (8-rem));

		// Mask out bits beyond width of display
		// TODO
	}

	return bits;
}

int Buffer::getWidth() {
return _width;
}

int Buffer::getHeight() {
return _height;
}

int Buffer::getPitchBytes() {
return _pitchBytes;
}

