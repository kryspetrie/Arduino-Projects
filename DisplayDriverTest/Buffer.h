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

enum BlendMode
{
	BUF_COPY = 0,
	BUF_OR = 1,
	BUF_AND = 2
};

class Buffer {
public:
	Buffer(const int width, const int height, const int pitchBytes, uint8_t* buff);

	// Full buffer operators
	void clear(bool val = 0);
	void clearRect(int x, int y, int width, int height, bool val = 0);
	void printSerial(char ones, char zeros);

	// Single bit operators
	void setBit(int x, int y, bool val);
	bool getBit(int x, int y);

	// Multiple bit operators
	void set8Bit(int x, int y, uint8_t data, BlendMode m = BUF_COPY);
	uint8_t get8Bit(int x, int y);

	// Getters
	int getWidth();
	int getHeight();
	int getPitchBytes();

private:
	const int _width;
	const int _height;
	const int _pitchBytes;
	uint8_t* _buff;
};

} /* namespace Led */
#endif /* BUFFER_H_ */
