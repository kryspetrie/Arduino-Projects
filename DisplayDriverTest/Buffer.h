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

// Enable the following as needed

namespace Display {

class Buffer {
public:
	Buffer(const int width, const int height, const int pitchBytes, uint8_t* buff);

	// Full buffer operations
	void clear();
	void clear(Color color);
	void printSerial(char ones = '1', char zeros = '0');

	// Buffer clear color
	void setColor(Color color);
	Color getColor();

	// Shape operations
	void clearRect(int x, int y, int width, int height);
	void clearRect(int x, int y, int width, int height, Color color);

	// 1-bit operations
	void setBit(int x, int y, Color color);
	Color getBit(int x, int y);

	// 8-bit operations
	void set8Bit(int x, int y, uint8_t data);
	uint8_t get8Bit(int x, int y);

	// Raw byte operations
	void setByte(unsigned int byteIndex, uint8_t data, unsigned int yIndex = 0);
	uint8_t getByte(unsigned int byteIndex, unsigned int yIndex = 0);

	// Raw buffer operations
	void clearRaw(Color color = BLACK);
	void fillRaw(uint8_t pattern);

	// Getters
	int getWidth();
	int getHeight();
	int getPitchBytes();
	int getSize();

public:
	// make private
	void fastHLine(int x, int y, int width, Color colorl);
	void memsetColor(uint8_t* buff, Color color, size_t bytes);

private:
	const int _width;
	const int _height;
	const int _pitchBytes;
	uint8_t* _buff;
	Color _color;
};

} /* namespace Led */
#endif /* BUFFER_H_ */
