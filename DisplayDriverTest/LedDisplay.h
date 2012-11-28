/*
 * LedDisplay.h
 *
 *  Created on: Nov 24, 2012
 *      Author: cpetrie
 */

#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_

#include "Arduino.h"

namespace Led {

class LedDisplay {
public:
	LedDisplay();
	virtual ~LedDisplay();
};

}
#endif /* LEDDISPLAY_H_ */
