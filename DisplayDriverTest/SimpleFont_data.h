/*
 * SimpleFont_data.h
 *
 *  Created on: Dec 11, 2012
 *      Author: cpetrie
 */

#ifndef SIMPLEFONT_DATA_H_
#define SIMPLEFONT_DATA_H_

#include <avr/pgmspace.h>
#include "SimpleFont.h"

// Put the data in Program Memory
#define PROGMEM_ __attribute__((section(".progmem.data")))

// Error bitmap data
static prog_uint32_t PROGMEM_ _errBitmap = 0x0a5a5a;

// Digit bitmap data
#ifdef _SF_DIGIT
static prog_uint32_t PROGMEM_ _digit[] = {
	0x06b9d6 /*0*/, 0x026227 /*1*/, 0x0e178f /*2*/, 0x0f171f /*3*/, 0x099f11 /*4*/,
	0x0f8e1f /*5*/, 0x078f9f /*6*/, 0x0f1224 /*7*/, 0x0f969f /*8*/, 0x0f9f11 /*9*/
};
#endif

// Alpha bitmap data
#ifdef _SF_ALPHA
static prog_uint32_t PROGMEM_ _alpha[] = {
	0x069f99 /*A*/, 0x0e9f9e /*B*/, 0x069896 /*C*/, 0x0e999e /*D*/,
	0x0f8e8f /*E*/, 0x0f8e88 /*F*/, 0x078b97 /*G*/, 0x099f99 /*H*/, 0x0f444f /*I*/,
	0x0f22ae /*J*/, 0x09aca9 /*K*/, 0x08888f /*L*/, 0x09ff99 /*M*/, 0x09dfb9 /*N*/,
	0x069996 /*O*/, 0x0e9f88 /*P*/, 0x0699a7 /*Q*/, 0x0e99e9 /*R*/, 0x078f1e /*S*/,
	0x0f4444 /*T*/, 0x099996 /*U*/, 0x099952 /*V*/, 0x0999f6 /*W*/, 0x099669 /*X*/,
	0x09972c /*Y*/, 0x0f124f /*Z*/
};
#endif

// Alpha bitmap data (BOLD style)
#ifdef _SF_ALPHA_BOLD
static prog_uint32_t PROGMEM_ _alphaBold[] = {
	0x06dfdd /*A*/, 0x0edfde /*B*/, 0x06dcd6 /*C*/, 0x0eddde /*D*/,
	0x0fcecf /*E*/, 0x0fcecc /*F*/, 0x07cfd7 /*G*/, 0x0ddfdd /*H*/, 0x0f666f /*I*/,
	0x0f33bf /*J*/, 0x0ddedd /*K*/, 0x0ccccf /*L*/, 0x09ff99 /*M*/, 0x09dfb9 /*N*/,
	0x06ddd6 /*O*/, 0x0edfcc /*P*/, 0x0699a7 /*Q*/, 0x0edded /*R*/, 0x07cf1e /*S*/,
	0x0f6666 /*T*/, 0x0dddd6 /*U*/, 0x0ddd52 /*V*/, 0x0999f6 /*W*/, 0x099669 /*X*/,
	0x09972c /*Y*/, 0x0f36cf /*Z*/
};
#endif

// Punctuation bitmap data (1)
#ifdef _SF_PUNC1
static prog_uint32_t PROGMEM_ _punc1[] = {
	0x000000 /* */, 0x066602 /*!*/, 0x055500 /*"*/, 0x05f5f5 /*#*/,
	0x07af5e /*$*/, 0x0b264d /*%*/, 0x075ebd /*&*/, 0x062400 /*'*/,
	0x024442 /*(*/, 0x042224 /*)*/, 0x00a4a0 /***/, 0x004e40 /*+*/,
	0x000624 /*,*/, 0x000f00 /*-*/, 0x000066 /*.*/, 0x012648 /*/*/
};
#endif

// Punctuation bitmap data (2)
#ifdef _SF_PUNC2
prog_uint32_t PROGMEM_ _punc2[] = {
	0x066066 /*:*/, 0x066024 /*;*/, 0x036c63 /*<*/, 0x00f0f0 /*=*/,
	0x0c636c /*>*/, 0x069206 /*?*/, 0x069356 /*@*/
};
#endif

// Punctuation bitmap data (3)
#ifdef _SF_PUNC3
prog_uint32_t PROGMEM_ _punc3[] = {
	0x064446 /*[*/, 0x084621 /*\*/, 0x062226 /*]*/, 0x069000 /*^*/,
	0x00000f /*_*/, 0x0c6200 /*`*/
};
#endif

// Punctuation bitmap data (4)
#ifdef _SF_PUNC4
prog_uint32_t PROGMEM_ _punc4[] = {
	0x024242 /*{*/, 0x066666 /*|*/, 0x042424 /*}*/, 0x000db0 /*~*/};
#endif

uint32_t resolve(uint32_t& data) { return pgm_read_dword(&data); }

#endif /* SIMPLEFONT_DATA_H_ */
