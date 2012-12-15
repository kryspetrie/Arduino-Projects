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
#include "Common.h"

namespace Display {

enum FontStyle {
	NOSTYLE = 0,
	BOLD = 1,
	ITALIC = 2
};

class Font {
public:
	Font(Buffer* buff);
	virtual ~Font();

	// Pure Virtual
	virtual void drawChar(int x, int y, char c) = 0;
	virtual void drawString(int x, int y, const char* string) = 0;
	virtual uint8_t getHeight() = 0;
	virtual uint8_t getWidth() = 0;

	// Default behaviors
	virtual uint8_t getKerning();
	virtual void setKerning(uint8_t kerning);

	virtual uint8_t getSpacing();
	virtual void setSpacing(uint8_t spacing);

	virtual void setColor(Color c);
	virtual Color getColor();

	virtual void setStyle(FontStyle style);
	virtual FontStyle getStyle();

protected:
	Buffer* _buff;
	uint8_t _spacing;
	uint8_t _kerning;
	Color _color;
	FontStyle _style;
};

} /* namespace Led */
#endif /* FONT_H_ */
