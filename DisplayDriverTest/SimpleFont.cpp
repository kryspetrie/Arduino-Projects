/*
 * SimpleFont.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#include "SimpleFont.h"
#include "SimpleFont_data.h"

using namespace Display;

SimpleFont::SimpleFont(Buffer* buff) :
		Font(buff) {
	_spacing = _height + 1;
	_kerning = 2;
}

SimpleFont::~SimpleFont() {}

void SimpleFont::drawChar(int x, int y, char c) {

	// Get the character bitmap
	uint32_t bitmap = getBitmap(c);

	// Set the color of the bitmap
	if (_color == BLACK)
		bitmap = ~bitmap;

	// Loop over the rows
	for (char y1 = y + _height - 1; y1 >= y; y1--) {

		// Get the row
		uint8_t curRow = (bitmap & 0x0f) << 4;

		// Draw the row
		_buff->set8Bit(x, y1, curRow, 0xf0);

		// Shift the bitmap
		bitmap >>= 4;
	}

//	// Generic version
//
//	// Loop across the height
//	for (int h = _height - 1; h >= 0; h--) {
//
//		// loop across the width
//		for (int w = _width - 1; w >= 0; w--) {
//
//			// Set only bits that are 1's
//			if (bitmap & 0x01)
//				_buff->setBit(x + w, y + h, _color);
//
//			// Shift out a bit
//			bitmap >>= 1;
//		}
//	}
}

void SimpleFont::drawString(int x, int y, const char* string) {

	// Write one line
	while (*string != 0) {
		drawChar(x, y, *string);
		string++;
		x += (_width + _kerning);
	}
}

uint8_t SimpleFont::getHeight() {
	return _height;
}

uint8_t SimpleFont::getWidth() {
	return _width;
}

//see http://ascii-table.com/
uint32_t SimpleFont::getBitmap(char c) {

	// Get digit bitmap
#ifdef _SF_DIGIT
	if (c >= '0' && c <= '9')
		return resolve(_digit[c - '0']);
#endif

	c = toUpperCase(c);

	// Get alpha bitmap
	if (c >= 'A' && c <= 'Z') {

		// Bold Style
#ifdef _SF_ALPHA_BOLD
		if (_style == BOLD)
			return resolve(_alphaBold[c - 'A']);
#endif
		// Default alpha
#ifdef _SF_ALPHA
		return resolve(_alpha[c - 'A']);
#endif
	}

	// Get punc1 bitmap
#ifdef _SF_PUNC1
	if (c >= ' ' && c <= '/')
		return resolve(_punc1[c - ' ']);
#endif

	// Get punc2 bitmap
#ifdef _SF_PUNC2
	if (c >= ':' && c <= '@')
		return resolve(_punc2[c - ':']);
#endif

	// Get punc3 bitmap
#ifdef _SF_PUNC3
	if (c >= '[' && c <= '`')
		return resolve(_punc3[c - '[']);
#endif

	// Get punc4 bitmap
#ifdef _SF_PUNC4
	if (c >= '{' && c <= '~')
		return resolve(_punc4[c - '{']);
#endif

	// Return the "error" bitmap
	return resolve(_errBitmap);
}

