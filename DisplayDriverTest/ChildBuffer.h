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

class ChildBuffer: private Display::Buffer {
public:
	ChildBuffer(const Rect window, Buffer &buffer);
	virtual ~ChildBuffer();

	// Override Full buffer operations
	virtual void clear();
	virtual void clear(Color color);
	virtual void printSerial(char ones = '1', char zeros = '0');

	// Override Shape operations
	virtual void clearRect(Rect& rect);
	virtual void clearRect(Rect& rect, Color color);

	// Override 1-bit operations
	virtual void setBit(int x, int y, Color color);
	virtual Color getBit(int x, int y);

	// Override 8-bit operations
	virtual void set8Bit(int x, int y, uint8_t data);
	virtual uint8_t get8Bit(int x, int y);

	// Override Raw byte operations
	virtual void setByte(unsigned int byteIndex, uint8_t data, unsigned int yIndex = 0);
	virtual uint8_t getByte(unsigned int byteIndex, unsigned int yIndex = 0);

	// Override Raw buffer operations
	virtual void clearRaw();
	virtual void clearRaw(Color color);
	virtual void fillRaw(uint8_t pattern);

	// Override Getters
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPitchBytes();
	virtual int getSize();

protected:
	ChildBuffer();
};

} /* namespace Display */
#endif /* CHILDBUFFER_H_ */
