/*
 * Buffer.h
 *
 *  Created on: Dec 13, 2012
 *      Author: cpetrie
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Common.h"

namespace Display {

class Buffer {
public:
	Buffer(){};
	virtual ~Buffer(){};

	// Full buffer operations
	virtual void clear() = 0;
	virtual void clear(Color color) = 0;
	virtual void printSerial(char ones, char zeros) = 0;

	// Buffer clear color
	virtual void setColor(Color color) = 0;
	virtual Color getColor() = 0;

	// Shape operations
	virtual void clearRect(Rect& rect) = 0;
	virtual void clearRect(Rect& rect, Color color) = 0;

	// 1-bit operations
	virtual void setBit(int x, int y, Color color) = 0;
	virtual Color getBit(int x, int y) = 0;

	// 8-bit operations
	virtual void set8Bit(int x, int y, uint8_t data) = 0;
	virtual uint8_t get8Bit(int x, int y) = 0;

	// Getters
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

protected:
	virtual void _fastHLine(int x, int y, int width, Color color) = 0;
	virtual void _printSerial(char ones, char zeros);
};

} /* namespace Display */
#endif /* BUFFER_H_ */
