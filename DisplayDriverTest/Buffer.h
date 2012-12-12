/*
 * Buffer.h
 *
 *  Created on: Nov 25, 2012
 *      Author: cpetrie
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Arduino.h"
#include "Common.h"

namespace Display {

class Rect {
public:
	Rect();
	Rect(int x0_, int y0_, int width_, int height_);
	void set(int x0_, int y0_, int width_, int height_);

public:
	int x0, y0;
	int width, height;
};

class Buffer {
public:
	Buffer(const int width, const int height, const int pitchBytes, uint8_t* buff);
	virtual ~Buffer();

	// Full buffer operations
	virtual void clear();
	virtual void clear(Color color);
	virtual void printSerial(char ones = '1', char zeros = '0');

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
	virtual uint8_t get8Bit(int x, int y);

	// Raw byte operations
	virtual void setByte(unsigned int byteIndex, uint8_t data, unsigned int yIndex = 0);
	virtual uint8_t getByte(unsigned int byteIndex, unsigned int yIndex = 0);

	// Raw buffer operations
	virtual void clearRaw();
	virtual void clearRaw(Color color);
	virtual void fillRaw(uint8_t pattern);

	// Getters
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPitchBytes();
	virtual int getSize();

protected:
	Buffer();
	void fastHLine(int x, int y, int width, Color colorl);
	void memsetColor(uint8_t* buff, Color color, size_t bytes);
	const int _width;
	const int _height;
	const int _pitchBytes;
	uint8_t* _buff;
	Color _color;
};

}
#endif /* BUFFER_H_ */
