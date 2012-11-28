/*
 * SimpleFont.h
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#ifndef SIMPLEFONT_H_
#define SIMPLEFONT_H_

#include "Font.h"
#include "Buffer.h"
#include "avr/io.h"
#include "avr/pgmspace.h"

namespace Led {

class SimpleFont: public Font {
public:
	SimpleFont(Buffer* buff);
	virtual ~SimpleFont();

	// Implementations
	virtual void drawChar(int x, int y, char c);
	virtual void drawString(int x, int y, char* string);
	virtual uint8_t getHeight();
	virtual uint8_t getWidth();

private:
	uint32_t getBitmap(char c);

private:
	// Const dimensions
	static const uint8_t width = 4;
	static const uint8_t height = 5;

	// Const bitmaps
	static const uint32_t fontArray[] PROGMEM = {
		0x06b9d6, // '0'
		0x026227, // '1'
		0x0e178f, // '2'
		0x0f171f, // '3'
		0x099f11, // '4'
		0x0f8e1f, // '5'
		0x078f9f, // '6'
		0x0f1224, // '7'
		0x0f969f, // '8'
		0x0f9f11  // '9'
	};
};

} /* namespace Led */
#endif /* SIMPLEFONT_H_ */
