/*
 * SimpleFont.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#include "SimpleFont.h"

using namespace Display;

// Font bitmap data
uint32_t fontArray[] = {
	0x06b9d6, // '0'
	0x026227, // '1'
	0x0e178f, // '2'
	0x0f171f, // '3'
	0x099f11, // '4'
	0x0f8e1f, // '5'
	0x078f9f, // '6'
	0x0f1224, // '7'
	0x0f969f, // '8'
	0x0f9f11  // '9'
};

SimpleFont::SimpleFont(Buffer* buff) : Font(buff) {
	_kerning = 1;
	_spacing = _height + 1;
}

SimpleFont::~SimpleFont() {}

void SimpleFont::drawChar(int x, int y, char c) {
	uint32_t bitmap;
	bitmap = getBitmap(c);

	// Loop across the height
	for (int h = _height-1; h >= 0; h--) {

		// loop across the width
		for (int w = _width-1; w >= 0; w--) {

			// Set only bits that are 1's
			if (bitmap & 0x01)
				_buff->setBit(x+w, y+h, _color);

			// Shift out a bit
			bitmap >>= 1;
		}
	}
}

void SimpleFont::drawString(int x, int y, char* string) {
	// TODO implement this using writeChar!
}

uint8_t SimpleFont::getHeight() {
	return _height;
}

uint8_t SimpleFont::getWidth() {
	return _width;
}

uint32_t SimpleFont::getBitmap(char c) {
	uint32_t bitmap(0x0);

	// convert character to upper case
	c = toUpperCase(c);

	// Get the bitmap from the font array
	//   see http://ascii-table.com/
	if (c >= '0' && c <= '9'){
		bitmap = fontArray[c - '0'];
	}

	return bitmap;
}

