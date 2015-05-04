#ifndef __GENTBL_H__
#define __GENTBL_H__

#include <stdint.h>

typedef uint8_t w8;
typedef uint16_t w16;
typedef uint32_t w32;
typedef uint64_t w64;

#if (WORD_SIZE == 8)
typedef w8 wtype;
#elif (WORD_SIZE == 16)
typedef w16 wtype;
#elif (WORD_SIZE == 32)
typedef w32 wtype;
#elif (WORD_SIZE == 64)
typedef w64 wtype;
#else
#error "illegal WORD_SIZE: must be 8,16,32,or 64"
#endif

#endif
