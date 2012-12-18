/*
 * Buffer2D.h
 *
 *  Created on: Nov 25, 2012
 *      Author: cpetrie
 */

#ifndef BUFFER2D_H_
#define BUFFER2D_H_

#include "Arduino.h"
#include "Common.h"
#include "Buffer.h"

namespace Display {

class Buffer2D : public Buffer {
public:
	Buffer2D(const int width, const int height, const int pitchBytes, uint8_t* buff);
	virtual ~Buffer2D();

	// Interface Functions
	/////////////////////////////////////////////////////////////////

	// Full buffer operations
	virtual void clear();
	virtual void clear(Color color);
	virtual void printSerial(char ones, char zeros);

	// Buffer clear color
	virtual void setColor(Color color);
	virtual Color getColor();

	// Shape operations
	virtual void clearRect(Rect& rect);
	virtual void clearRect(Rect& rect, Color color);

	// 1-bit operations
	virtual void setBit(int x, int y, Color color);
	virtual Color getBit(int x, int y);

	// 8-bit operations
	virtual void set8Bit(int x, int y, uint8_t data);
	virtual void set8Bit(int x, int y, uint8_t data, uint8_t mask);
	virtual uint8_t get8Bit(int x, int y);

	// Getters
	virtual int getWidth();
	virtual int getHeight();

	// Line operations
	void fastHLine(int x, int y, int width, Color color);

	// Buffer2D Specific Functions
	/////////////////////////////////////////////////////////////////

	// Raw byte operations
	virtual void setByte(unsigned int byteIndex, uint8_t data, unsigned int yIndex = 0);
	virtual uint8_t getByte(unsigned int byteIndex, unsigned int yIndex = 0);

	// Raw buffer operations
	virtual void clearRaw();
	virtual void clearRaw(Color color);
	virtual void fillRaw(uint8_t pattern);

	// Getters
	virtual int getPitchBytes();
	virtual int getSize();

protected:
	void memsetColor(uint8_t* buff, Color color, size_t bytes);

private:
	Buffer2D();
	bool outOfBounds(int x, int y);

	const int _width;
	const int _height;
	const int _pitchBytes;
	uint8_t* _buff;
	Color _color;
};

}
#endif /* BUFFER_H_ */
