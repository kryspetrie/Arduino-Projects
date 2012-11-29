/*
 * SimpleFont.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#include "SimpleFont.h"
#include "avr/io.h"
#include "avr/pgmspace.h"

using namespace Led;

// Const bitmaps
static uint32_t fontArray[] /*PROGMEM*/ = {
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

