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

namespace Display {

/**
 * Use the following to enable
 *  or disable font features.
 */
#define _SF_DIGIT 			/* 0123456789 */
#define _SF_ALPHA			/* ABCDEFGHIJKLMNOPQRSTUVWXYZ  normal */
#define _SF_ALPHA_BOLD		/* ABCDEFGHIJKLMNOPQRSTUVWXYZ  bold */
#define _SF_PUNC1			/*  !"#$%&'()*+,-./ */
#define _SF_PUNC2			/* :;<=>?@ */
#define _SF_PUNC3			/* [\]^_` */
#define _SF_PUNC4			/* {|}~ */

class SimpleFont: public Font {
public:
	SimpleFont(Buffer* buff);
	virtual ~SimpleFont();

	// Implementations
	virtual void drawChar(int x, int y, char c);
	virtual void drawString(int x, int y, const char* string);
	virtual uint8_t getHeight();
	virtual uint8_t getWidth();

private:
	uint32_t getBitmap(char c);

private:
	// Const dimensions
	static const uint8_t _width = 4;
	static const uint8_t _height = 5;
};

} /* namespace Led */
#endif /* SIMPLEFONT_H_ */
