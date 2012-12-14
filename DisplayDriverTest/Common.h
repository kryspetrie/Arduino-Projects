/*
 * Common.h
 *
 *  Created on: Dec 6, 2012
 *      Author: cpetrie
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "Arduino.h"

namespace Display {

class Rect {
public:
	Rect() :
			x0(0), y0(0), width(1), height(1) {
	}

	Rect(int x0_, int y0_, int width_, int height_) :
			x0(x0_), y0(y0_), width(width_), height(height_) {
	}

	void set(int x0_, int y0_, int width_, int height_) {
		x0 = x0_;
		y0 = y0_;
		width = width_;
		height = height_;
	}

public:
	int x0, y0;
	int width, height;
};

enum Color {
	BLACK = 0, WHITE = 1
};

}

#endif /* COMMON_H_ */
