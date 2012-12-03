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
Buffer::Buffer(const int width, const int height, const int pitchBytes,
		uint8_t* buff) :
		_width(width), _height(height), _pitchBytes(pitchBytes), _buff(buff) {
	clear();
}

void Buffer::clear(bool val) {
	uint8_t bits = val ? 0xFF : 0x00;
	memset(_buff, bits, getSize());
}

void Buffer::fill(uint8_t pattern) {
	memset(_buff, pattern, getSize());
}

void Buffer::setByte(unsigned int byteIndex, uint8_t data,
		unsigned int yIndex) {
	int i = byteIndex * (yIndex + 1);

	// Set data, if not over end of buffer
	if (i < getSize())
		_buff[i] = data;
}

uint8_t Buffer::getByte(unsigned int byteIndex, unsigned int yIndex) {
	int i = byteIndex * (yIndex + 1);
	uint8_t retVal(0);

	// Set data, if not over end of buffer
	if (i < getSize())
		retVal = _buff[i];

	return retVal;
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
	if (x > _width || x < 0 || y > _height || y < 0)
		return;

	// Get byte pointer that contains the bit
	uint8_t* bitBytePtr = _buff + (_pitchBytes * y) + (x / 8);

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
	if (x > _width || x < 0 || y > _height || y < 0)
		return false;

	// Get byte that contains the bit
	uint8_t bitByte = *(_buff + (_pitchBytes * y) + (x / 8));

	// Shift the byte to extract the desired bit
	uint8_t bit = (bitByte << (x % 8)) & 0x80;

	return bit ? true : false;
}

void Buffer::set8Bit(int x, int y, uint8_t data) {

	uint8_t bits1(data), bits2(data);

	// Return if non-existent row
	if (y > _height || y < 0)
		return;

	// Special case for negative x-index
	if (x < 0) {
		int bitsInBuffer = x + 8;

		// If there are bits to set within the buffer
		if (bitsInBuffer > 0) {

			// Get the pointer to the first 8 bits in the row
			uint8_t* firstBitsInRow = _buff + (y * _pitchBytes);

			// Clear the bits to set
			*firstBitsInRow &= (0xFF >> bitsInBuffer);

			// Shift the data bits to the proper position
			bits1 <<= (8 - bitsInBuffer);

			// Set the bits in the buffer
			*firstBitsInRow |= bits1;
		}

		return;
	}

	// Calculate the index information into the byte array
	uint8_t byteIndex = x / 8;
	uint8_t byteRem = x % 8;

	// Calculate the row's last byte's index
	uint8_t lastByteIndex = _pitchBytes - 1;

	// Calculate the mask for bits beyond display width
	uint8_t maskBits = 0xFF << (8 - _width % 8);

	// Get byte that will contain the most significant part of the 8 bits
	uint8_t* bitsByte1 = _buff + (_pitchBytes * y) + byteIndex;

	// Shift data bits to align for saving into first byte
	bits1 >>= byteRem;

	// Mask out bits beyond width of display
	if (byteIndex == lastByteIndex)
		bits1 &= maskBits;

	// Clear the bits to set
	*bitsByte1 &= (0xFF << (8 - byteRem));

	// Set the first byte containing some of the 8 bits
	*bitsByte1 |= bits1;

	// If we need to set bits in the following byte as well
	if (byteRem > 0 && (byteIndex < lastByteIndex)) {

		// Get byte that will contain the least significant part of the 8 bits
		uint8_t* bitsByte2 = bitsByte1 + 1;

		// Shift data bits to align for saving into second byte
		bits2 <<= (8 - byteRem);

		// Mask out bits beyond width of display
		if (byteIndex + 1 == lastByteIndex)
			bits2 &= maskBits;

		// Clear the bits to set
		*bitsByte2 &= (0xFF >> byteRem);

		// Set the second byte containing the rest of the 8 bits
		*bitsByte2 |= bits2;
	}
}

uint8_t Buffer::get8Bit(int x, int y) {

	uint8_t bits1(0), bits2(0);

	// Return if non-existent row
	if (y > _height || y < 0)
		return 0;

	// Special case for negative x-index
	if (x < 0) {
		uint8_t retNeg(0);
		int bitsInBuffer = x + 8;

		// If there are requested bits within the buffer
		if (bitsInBuffer > 0) {

			// Get the first 8 bits in the row
			uint8_t firstBitsInRow = _buff[y * _pitchBytes];

			// Shift the bits to the proper position
			retNeg = firstBitsInRow >> (8 - bitsInBuffer);
		}

		return retNeg;
	}

	// Calculate the index information into the byte array
	uint8_t byteIndex = x / 8;
	uint8_t byteRem = x % 8;

	// Calculate the row's last byte's index
	uint8_t lastByteIndex = _pitchBytes - 1;

	// Calculate the mask for bits beyond display width
	uint8_t maskBits = 0xFF << (8 - _width % 8);

	// Get byte that contains the most significant part of the 8-bits
	uint8_t* bitsByte1 = _buff + (_pitchBytes * y) + byteIndex;

	// Get 1st Byte containing bits
	bits1 = *bitsByte1;

	// Mask out bits beyond width of display
	if (byteIndex == lastByteIndex) {
		bits1 &= maskBits;
	}

	// Shift the bits by the remainder to realign left
	bits1 <<= byteRem;

	// If we need data from the following byte as well
	if (byteRem > 0 && (byteIndex < lastByteIndex)) {

		// Get byte that contains the least significant part of the 8 bits
		uint8_t* bitsByte2 = bitsByte1 + 1;

		// Get 2nd Byte containing bits
		bits2 = *bitsByte2;

		// Mask out bits beyond width of display
		if (byteIndex + 1 == lastByteIndex) {
			bits2 &= maskBits;
		}

		// Shift the byte to extract the desired bits
		bits2 >>= (8 - byteRem);
	}

	return bits1 | bits2;
}

void Buffer::fastHLine(int x, int y, int width, bool val) {
	// TODO fix this! It's wrong!

	// Determine bit pattern
	uint8_t writeVal = val ? 0xFF : 0x00;

	// Calculate the index information
	uint8_t startRem = x % 8;
	uint8_t endRem = (x + width) % 8;
	int nMiddleBytes = (width - startRem - endRem) / 8;

	// Write first 8 (slow)
	if (startRem > 0) {
		for (int i = 0; (i < width) && (i < 8-startRem); i++)
			setBit(x + i, y, val);
	}

/*	// Write the middle bytes (fast)
	if (nMiddleBytes > 0) {
		uint8_t* middleByte = _buff + (y * _pitchBytes) + ((x + 7) / 8);
		memset(middleByte, writeVal, nMiddleBytes);
	}
*/
	// Write last 8 (slow)
	if (endRem > 0) {
		int lastX = x + width - endRem;
		for (int i = 0; (i < width) && (i < 8-endRem); i++)
			setBit(lastX + i, y, val);
	}
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

int Buffer::getSize() {
	return (_pitchBytes * _height);
}
