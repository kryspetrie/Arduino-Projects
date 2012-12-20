/*
 * Font.cpp
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#include "Font.h"
using namespace Display;

Font::Font(Buffer& buff) : _buff(&buff), _spacing(0), _kerning(0), _color(WHITE), _style(NOSTYLE){}

Font::~Font() {}

uint8_t Font::getSpacing() {
	return _spacing;
}

void Font::setSpacing(uint8_t spacing) {
	_spacing = spacing;
}

void Font::setColor(Color color){
	_color = color;
}

Color Display::Font::getColor() {
	return _color;
}

void Display::Font::setStyle(FontStyle style) {
	_style = style;
}

uint8_t Display::Font::getKerning() {
	return _kerning;
}

void Display::Font::setKerning(uint8_t kerning) {
	_kerning = kerning;
}

FontStyle Display::Font::getStyle() {
	return _style;
}
