/*
 * Buffer.cpp
 *
 *  Created on: Nov 25, 2012
 *      Author: cpetrie
 */

#include "Buffer.h"
using namespace Display;

Rect::Rect() :
		x0(0), y0(0), width(1), height(1) {
}

Rect::Rect(int x0_, int y0_, int width_, int height_) :
		x0(x0_), y0(y0_), width(width_), height(height_) {
}

void Rect::set(int x0_, int y0_, int width_, int height_) {
	x0 = x0_;
	y0 = y0_;
	width = width_;
	height = height_;
}

/**
 * Creates a buffer object with a certain width/height, using the
 *  provided buffer.  The provided buffer MUST BE equal to at least
 *  pitchBytes * height.
 *
 *  \param width The width of the image buffer in pixels
 *  \param height The height of image buffer in pixels
 *  \param pitchBytes The number of bytes provided for each row.
 *  	This must be at least floor( (width + 7)/8 ) bytes
 *  \param buff pointer to the display buffer array
 */
Buffer::Buffer(const int width, const int height, const int pitchBytes, uint8_t* buff) :
		_width(width), _height(height), _pitchBytes(pitchBytes), _buff(buff), _color(BLACK) {
	clear(_color);
}

Buffer::~Buffer() {
}

void Buffer::clear() {
	clear(_color);
}

void Buffer::clear(Color color) {

	for (int y = 0; y < _height; y++)
		fastHLine(0, y, _width, color);
}

void Buffer::clearRect(Rect& rect) {
	clearRect(rect, _color);
}

void Buffer::clearRect(Rect& rect, Color color) {
	int lastRow = rect.y0 + rect.height;

	// Note: fastHLine will handle input error conditions
	for (int row = rect.y0; row < lastRow; row++)
		fastHLine(rect.x0, row, rect.width, color);
}

void Buffer::clearRaw() {
	clearRaw(_color);
}

void Buffer::clearRaw(Color color) {
	memsetColor(_buff, color, getSize());
}

void Buffer::fillRaw(uint8_t pattern) {
	memset(_buff, pattern, getSize());
}

void Buffer::setByte(unsigned int byteIndex, uint8_t data, unsigned int yIndex) {
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
			Color color = getBit(w, h);

			// Print the bit
			char bitChar = (color == WHITE) ? ones : zeros;
			Serial.print(bitChar);
		}

		// Print an end-line for each row
		Serial.println("");
	}
}

void Buffer::setBit(int x, int y, Color color) {

	// Check input variables
	if (x >= _width || x < 0 || y >= _height || y < 0)
		return;

	// Get byte pointer that contains the bit
	uint8_t* bitBytePtr = _buff + (_pitchBytes * y) + (x / 8);

	// Shift over the bit to change
	uint8_t bit = 0x01 << (7 - (x % 8));

	if (color == WHITE) {
		*bitBytePtr |= bit;  // set the bit
	} else {
		*bitBytePtr &= ~bit; // clear the bit
	}
}

Color Buffer::getBit(int x, int y) {

	// Check input variables
	if (x >= _width || x < 0 || y >= _height || y < 0)
		return _color;

	// Get byte that contains the bit
	uint8_t bitByte = *(_buff + (_pitchBytes * y) + (x / 8));

	// Shift the byte to extract the desired bit
	uint8_t bit = (bitByte << (x % 8)) & 0x80;

	return bit ? WHITE : BLACK;
}

void Buffer::set8Bit(int x, int y, uint8_t data) {

	uint8_t bits1(data), bits2(data);

	// Return if non-existent row
	if (y >= _height || y < 0)
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
	if (y >= _height || y < 0)
		return (_color == BLACK) ? 0xFF : 0x00;

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
	if (byteIndex == lastByteIndex)
		bits1 &= maskBits;

	// Shift the bits by the remainder to realign left
	bits1 <<= byteRem;

	// If we need data from the following byte as well
	if (byteRem > 0 && (byteIndex < lastByteIndex)) {

		// Get byte that contains the least significant part of the 8 bits
		uint8_t* bitsByte2 = bitsByte1 + 1;

		// Get 2nd Byte containing bits
		bits2 = *bitsByte2;

		// Mask out bits beyond width of display
		if (byteIndex + 1 == lastByteIndex)
			bits2 &= maskBits;

		// Shift the byte to extract the desired bits
		bits2 >>= (8 - byteRem);
	}

	return bits1 | bits2;
}

void Buffer::fastHLine(int x, int y, int width, Color color) {

	// Handle out-of-bounds X
	if (x > _width)
		return;

	// Handle out-of-bounds Y
	if (y < 0 || y >= _height)
		return;

	// Handle 0-width
	if (width == 0)
		return;

	// Handle negative width
	if (width < 0) {
		width = abs(width);
		x -= width;
	}

	// Handle negative X
	if (x < 0) {
		if (x + width < 0)
			return;

		// Realign at zero
		width = x + width;
		x = 0;
	}

	// Handle out-of-bounds width
	if (x + width > _width)
		width = _width - x;

	// Calculate indexes
	uint8_t startRem = x % 8;
	uint8_t endRem = (x + width) % 8;

	// Write first non-byte-aligned bits (slow)
	uint8_t fullByte1 = (startRem == 0) && (width >= 8) && (x + width <= _width);
	if (!fullByte1) {
		for (int i = 0; (i < width) && (i < 8 - startRem); i++)
			setBit(x + i, y, color);
	}

	// Write the middle byte-aligned 8-bit blocks (fast)
	uint8_t nMiddleBytes = (width - (8 - startRem) - endRem) / 8 + fullByte1;
	if (nMiddleBytes > 0) {
		uint8_t* middleByte = _buff + (y * _pitchBytes) + ((x + 7) / 8);
		memsetColor(middleByte, color, nMiddleBytes);
	}

	// Write last non-byte-aligned bits (slow)
	if (endRem > 0 && (startRem + width) > 8) {
		int lastBitsX = x + width - endRem;
		for (int i = 0; i < endRem; i++)
			setBit(lastBitsX + i, y, color);
	}
}

void Buffer::memsetColor(uint8_t* buff, Color color, size_t bytes) {
	uint8_t writeVal = (color == WHITE) ? 0xFF : 0x00;
	memset(buff, writeVal, bytes);
}

void Buffer::setColor(Color color) {
	_color = color;
}

Color Buffer::getColor() {
	return _color;
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
