/*
 * ChildBuffer.cpp
 *
 *  Created on: Dec 11, 2012
 *      Author: cpetrie
 */

#include "ChildBuffer2D.h"

namespace Display {

ChildBuffer2D::ChildBuffer2D(Rect window, Buffer& buffer) :
		_parentBuff(&buffer), _window(window){
}

ChildBuffer2D::~ChildBuffer2D() {
}

void ChildBuffer2D::clear() {
	_parentBuff->clearRect(_window);
}

void ChildBuffer2D::clear(Color color) {
	_parentBuff->clearRect(_window, color);
}

void ChildBuffer2D::printSerial(char ones, char zeros) {
	_printSerial(ones, zeros);
}

void ChildBuffer2D::clearRect(Rect& rect) {
	clearRect(rect, _parentBuff->getColor());
}

void ChildBuffer2D::clearRect(Rect& rect, Color color) {
	Rect tmpRect = rect;
	//TODO finish this
}

void ChildBuffer2D::setBit(int x, int y, Color color) {

	// Handle error cases
	if (outOfBounds(x, y))
		return;

	// Set the bit in the parent
	_parentBuff->setBit(x + _window.x0, y + _window.y0, color);
}

Color ChildBuffer2D::getBit(int x, int y) {

	// Handle error cases
	if (outOfBounds(x, y))
		return _parentBuff->getColor();

	// Get the bit from the parent
	return _parentBuff->getBit(x + _window.x0, y + _window.y0);
}

void ChildBuffer2D::set8Bit(int x, int y, uint8_t data) {
	set8Bit(x, y, data, 0xFF);
}

void ChildBuffer2D::set8Bit(int x, int y, uint8_t data, uint8_t mask) {
	//TODO finish this
}

uint8_t ChildBuffer2D::get8Bit(int x, int y) {
	//TODO finish this
	return 0;
}


int ChildBuffer2D::getWidth() {
	return _window.width;
}

int ChildBuffer2D::getHeight() {
	return _window.height;
}

bool ChildBuffer2D::outOfBounds(int x, int y) {
	return (x >= _window.x0 + _window.width  || x < _window.x0 ||
			y >= _window.y0 + _window.height || y < _window.y0);
}


} /* namespace Display */
