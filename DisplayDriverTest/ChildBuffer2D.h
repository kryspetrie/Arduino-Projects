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
	ChildBuffer2D(Rect window, Buffer &buffer);
	virtual ~ChildBuffer2D();

	// Interface Functions
	/////////////////////////////////////////////////////////////////

	// Wrap Full buffer operations
	virtual void clear();
	virtual void clear(Color color);
	virtual void printSerial(char ones, char zeros);

	// Wrap Shape operations
	virtual void clearRect(Rect& rect);
	virtual void clearRect(Rect& rect, Color color);

	// Wrap 1-bit operations
	virtual void setBit(int x, int y, Color color);
	virtual Color getBit(int x, int y);

	// Wrap 8-bit operations
	virtual void set8Bit(int x, int y, uint8_t data);
	virtual uint8_t get8Bit(int x, int y);

	// Getters
	virtual int getWidth();
	virtual int getHeight();

protected:
	ChildBuffer2D();
	Buffer* _parentBuff;
	Rect _window;

private:
	bool outOfBounds(int x, int y);
};

} /* namespace Display */
#endif /* CHILDBUFFER_H_ */
