/*
 * Font.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#include "Font.h"
using namespace Display;

Font::Font(Buffer* buff) : _buff(buff), _kerning(0), _spacing(0), _color(WHITE){}

Font::~Font() {}

uint8_t Font::getKerning() {
	return _kerning;
}

void Font::setKerning(uint8_t width) {
	_kerning = width;
}

uint8_t Font::getSpacing() {
	return _spacing;
}

void Font::setSpacing(uint8_t spacing) {
	_spacing = spacing;
}

void Font::setColor(Color color){
	_color = color;
}
