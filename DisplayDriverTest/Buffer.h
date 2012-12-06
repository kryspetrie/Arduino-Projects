/*
 * Buffer.h
 *
 *  Created on: Nov 25, 2012
 *      Author: cpetrie
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Arduino.h"

namespace Led {

class Buffer {
public:
	Buffer(const int width, const int height, const int pitchBytes, uint8_t* buff);

	// Full buffer operations
	void clear(bool val = 0);
	void printSerial(char ones, char zeros);

	// Shape operations
	void clearRect(int x, int y, int width, int height, bool val = 0);

	// 1-bit operations
	void setBit(int x, int y, bool val);
	bool getBit(int x, int y);

	// 8-bit operations
	void set8Bit(int x, int y, uint8_t data);
	uint8_t get8Bit(int x, int y);

	// Raw byte operations
	void setByte(unsigned int byteIndex, uint8_t data, unsigned int yIndex = 0);
	uint8_t getByte(unsigned int byteIndex, unsigned int yIndex = 0);

	// Raw buffer operations
	void clearRaw(bool val = 0);
	void fillRaw(uint8_t pattern);

	// Getters
	int getWidth();
	int getHeight();
	int getPitchBytes();
	int getSize();

public: // make private
	void fastHLine(int x, int y, int width, bool val);


private:
	const int _width;
	const int _height;
	const int _pitchBytes;
	uint8_t* _buff;
};

} /* namespace Led */
#endif /* BUFFER_H_ */
