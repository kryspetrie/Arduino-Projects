/*
 * ChildBuffer.cpp
 *
 *  Created on: Dec 11, 2012
 *      Author: cpetrie
 */

#include "ChildBuffer2D.h"

namespace Display {

ChildBuffer2D::ChildBuffer2D(Rect& window, Buffer& buffer) :
		_parentBuff(&buffer), _window(&window) {
}

ChildBuffer2D::~ChildBuffer2D() {
}

void ChildBuffer2D::clear() {
	_parentBuff->clearRect(*_window);
}

void ChildBuffer2D::clear(Color color) {
	_parentBuff->clearRect(*_window, color);
}

void ChildBuffer2D::printSerial(char ones, char zeros) {
	_printSerial(ones, zeros);
}

void ChildBuffer2D::setColor(Color color) {
	_parentBuff->setColor(color);
}

Color ChildBuffer2D::getColor() {
	return _parentBuff->getColor();
}

void ChildBuffer2D::setWindow(Rect& window) {
	_window = &window;
}

void ChildBuffer2D::clearRect(Rect& rect) {
	clearRect(rect, _parentBuff->getColor());
}

//TODO test this
void ChildBuffer2D::clearRect(Rect& rect, Color color) {
	Rect r(rect);

	// If we can clear the Rect region
	if (_constrainRect(r)) {

		// Put the Rect into parent buffer coordinates
		r.x0 += _window->x0;
		r.y0 += _window->y0;

		// Actually set the Rect region
		for (int h = 0; h < r.height; h++) {
			_parentBuff->fastHLine(r.x0, r.y0 + h, r.width, color);
		}
	}
}

void ChildBuffer2D::setBit(int x, int y, Color color) {

	// Handle error cases
	if (_outOfBounds(x, y))
		return;

	// Set the bit in the parent
	_parentBuff->setBit(x + _window->x0, y + _window->y0, color);
}

Color ChildBuffer2D::getBit(int x, int y) {

	// Handle error cases
	if (_outOfBounds(x, y))
		return _parentBuff->getColor();

	// Get the bit from the parent
	return _parentBuff->getBit(x + _window->x0, y + _window->y0);
}

void ChildBuffer2D::set8Bit(int x, int y, uint8_t data) {
	set8Bit(x, y, data, 0xFF);
}

// TODO Test this
void ChildBuffer2D::set8Bit(int x, int y, uint8_t data, uint8_t mask) {

	// Return if no bits could possibly be within the child buffer
	if (_outOfBounds8Bit(x, y))
		return;

	// Mask out left-most bits not in the child buffer
	if (x < 0)
		mask &= 0xFF >> -x;

	// Mask out right-most bits not in the child buffer
	int xOvershoot = (x + 8) - _window->width;
	if (xOvershoot > 0)
		mask &= 0xFF << xOvershoot;

	// Set the bits in the parent
	_parentBuff->set8Bit(x + _window->x0, y + _window->y0, mask);
}

// TODO Test this
uint8_t ChildBuffer2D::get8Bit(int x, int y) {

	// Get parent buffer color
	uint8_t byteColor = _parentBuff->getColor() == WHITE ? WHITEBYTE : BLACKBYTE;

	// Return background color if no bits could possibly be within the child buffer
	if (_outOfBounds8Bit(x, y))
		return byteColor;

	// Get the mask bits for where to mask to background color
	uint8_t mask = _createMask8Bit(x);

	// Get the parent buffer bits
	uint8_t retBits = _parentBuff->get8Bit(x, y);

	// Perform masking
	retBits &= mask;
	byteColor &= ~mask;

	// Return the combined bits
	return retBits | byteColor;
}

void ChildBuffer2D::fastHLine(int x, int y, int width, Color color) {

	// Fix negative width
	if (width < 0) {
		width = abs(width);
		x -= width;
	}

	// Fix negative x
	if (x < 0) {
		width += x;
		x = 0;
	}

	// Handle out-of-bounds
	if (x >= _window->width || y < 0 || y >= _window->height) {
		return;
	}

	// Fix out-of-bounds width
	if (x + width >= _window->width) {
		width = _window->width - x;
	}

	// Actually draw the line in the parent
	_parentBuff->fastHLine(x + _window->x0, y + _window->y0, width, color);
}

int ChildBuffer2D::getWidth() {
	return _window->width;
}

int ChildBuffer2D::getHeight() {
	return _window->height;
}

bool ChildBuffer2D::_outOfBounds(int x, int y) {
	return (x >= _window->x0 + _window->width || x < _window->x0 || y >= _window->y0 + _window->height
			|| y < _window->y0);
}

bool ChildBuffer2D::_outOfBounds8Bit(int x, int y) {
	return (y >= _window->height || y < 0 || x < -8 || x >= _window->width);
}

uint8_t ChildBuffer2D::_createMask8Bit(int x) {
	// Mask out left-most bits not in the child buffer
	uint8_t mask(0xFF);
	if (x < 0)
		mask &= 0xFF >> -x;

	// Mask out right-most bits not in the child buffer
	int xOvershoot = (x + 8) - _window->width;
	if (xOvershoot > 0)
		mask &= 0xFF << xOvershoot;

	return mask;
}

bool ChildBuffer2D::_constrainRect(Rect& r) {

	// Fix negative width
	if (r.width < 0) {
		r.width = abs(r.width);
		r.x0 -= r.width;
	}

	// Fix negative height
	if (r.height < 0) {
		r.height = abs(r.height);
		r.y0 -= r.height;
	}

	// Handle negative x0
	if (r.x0 < 0) {
		if (r.x0 + r.width < 0)
			return false;

		r.width += r.x0;
		r.x0 = 0;
	}

	// Handle negative y0
	if (r.y0 < 0) {
		if (r.y0 + r.height < 0)
			return false;

		r.height += r.y0;
		r.y0 = 0;
	}

	// Handle out-of-bounds x0
	if (r.x0 >= _window->width)
		return false;

	// Handle out-of-bounds y0
	if (r.y0 >= _window->height)
		return false;

	// Fix out-of-bounds width
	if (r.x0 + r.width >= _window->width)
		r.width = _window->width - r.x0 - 1;

	// Fix out-of-bounds height
	if (r.y0 + r.height >= _window->height)
		r.height = _window->height - r.y0 - 1;

	return true;
}

} /* namespace Display */
