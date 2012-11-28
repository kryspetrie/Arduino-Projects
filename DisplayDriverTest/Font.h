/*
 * Font.h
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#ifndef FONT_H_
#define FONT_H_

#include "Arduino.h"
#include "Buffer.h"

namespace Led {

class Font {
public:
	Font(Buffer* buff);
	virtual ~Font();

	// Pure Virtual
	virtual void writeChar(int x, int y, char c) = 0;
	virtual void writeString(int x, int y, char* string) = 0;
	virtual uint8_t getHeight() = 0;
	virtual uint8_t getWidth() = 0;

	// Default behaviors
	virtual uint8_t getKerning();
	virtual void setKerning(uint8_t width);
	virtual uint8_t getSpacing();
	virtual void setSpacing(uint8_t spacing);
	virtual void setInvert(bool invert);

protected:
	Buffer* _buff;
	uint8_t _kerning;
	uint8_t _spacing;
	bool _invert;

private:
};

} /* namespace Led */
#endif /* FONT_H_ */
