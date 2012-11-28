/*
 * SimpleFont.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#include "SimpleFont.h"

using namespace Led;

SimpleFont::SimpleFont(Buffer* buff) : Font(buff) {
	_kerning = 1;
	_spacing = height + 1;
}

SimpleFont::~SimpleFont() {}

void SimpleFont::drawChar(int x, int y, char c) {
	uint32_t bitmap;
	bitmap = getBitmap(c);

	// TODO implement this!
}

void SimpleFont::drawString(int x, int y, char* string) {
	// TODO implement this using writeChar!
}

uint8_t SimpleFont::getHeight() {
	return height;
}

uint8_t SimpleFont::getWidth() {
	return width;
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

