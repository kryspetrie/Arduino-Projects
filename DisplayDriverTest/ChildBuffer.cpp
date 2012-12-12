/*
 * ChildBuffer.cpp
 *
 *  Created on: Dec 11, 2012
 *      Author: cpetrie
 */

#include "ChildBuffer.h"

namespace Display {

ChildBuffer::ChildBuffer(const Rect window, Buffer& buffer) {
	//TODO finish this
}

ChildBuffer::~ChildBuffer() {
}

void ChildBuffer::clear() {
	//TODO finish this
}

void ChildBuffer::clear(Color color) {
	//TODO finish this
}

void ChildBuffer::printSerial(char ones, char zeros) {
	//TODO finish this
}

void ChildBuffer::clearRect(Rect& rect) {
	//TODO finish this
}

void ChildBuffer::clearRect(Rect& rect, Color color) {
	//TODO finish this
}

void ChildBuffer::setBit(int x, int y, Color color) {
	//TODO finish this
}

Color ChildBuffer::getBit(int x, int y) {
	//TODO finish this
	return BLACK;
}

void ChildBuffer::set8Bit(int x, int y, uint8_t data) {
	//TODO finish this
}

uint8_t ChildBuffer::get8Bit(int x, int y) {
	//TODO finish this
	return 0;
}

void ChildBuffer::setByte(unsigned int byteIndex, uint8_t data, unsigned int yIndex) {
	//TODO finish this
}

uint8_t ChildBuffer::getByte(unsigned int byteIndex, unsigned int yIndex) {
	//TODO finish this
	return 0;
}

void ChildBuffer::clearRaw() {
	//TODO finish this
}

void ChildBuffer::clearRaw(Color color) {
	//TODO finish this
}

void ChildBuffer::fillRaw(uint8_t pattern) {
	//TODO finish this
}

int ChildBuffer::getWidth() {
	//TODO finish this
	return 0;
}

int ChildBuffer::getHeight() {
	//TODO finish this
	return 0;
}

int ChildBuffer::getPitchBytes() {
	//TODO finish this
	return 0;
}

int ChildBuffer::getSize() {
	//TODO finish this
	return 0;
}

} /* namespace Display */
