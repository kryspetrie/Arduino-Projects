/*
 * ChildBuffer.h
 *
 *  Created on: Dec 11, 2012
 *      Author: cpetrie
 */

#ifndef CHILDBUFFER_H_
#define CHILDBUFFER_H_

#include "Buffer.h"

namespace Display {

class ChildBuffer2D: public Buffer {
public:
	ChildBuffer2D(Rect& window, Buffer& buffer);
	virtual ~ChildBuffer2D();

	// Interface Functions
	/////////////////////////////////////////////////////////////////

	// Wrap Full buffer operations
	virtual void clear();
	virtual void clear(Color color);
	virtual void printSerial(char ones, char zeros);

	// Wrap Parent Buffer clear color
	virtual void setColor(Color color);
	virtual Color getColor();

	// Wrap Shape operations
	virtual void clearRect(Rect& rect);
	virtual void clearRect(Rect& rect, Color color);

	// Wrap 1-bit operations
	virtual void setBit(int x, int y, Color color);
	virtual Color getBit(int x, int y);

	// Wrap 8-bit operations
	virtual void set8Bit(int x, int y, uint8_t data);
	virtual void set8Bit(int x, int y, uint8_t data, uint8_t mask);
	virtual uint8_t get8Bit(int x, int y);

	// Getters
	virtual int getWidth();
	virtual int getHeight();

	// Line operations
	virtual void fastHLine(int x, int y, int width, Color color);

	// Child Buffer Specific Functions
	/////////////////////////////////////////////////////////////////
	virtual void setWindow(Rect& window);

protected:
	ChildBuffer2D();
	Buffer* _parentBuff;
	Rect* _window;

private:
	bool _outOfBounds(int x, int y);
	bool _outOfBounds8Bit(int x, int y);
	uint8_t _createMask8Bit(int x);
	bool _constrainRect(Rect& r);
};

} /* namespace Display */
#endif /* CHILDBUFFER_H_ */
