

#include "stdint.h"
#include "general.h"
#ifndef expand

#define expand


void endOfLine(uint16_t* x, uint16_t* y);
void endOfBitmap(uint8_t*);
void deltaMove(uint16_t* x, uint16_t* y, uint16_t xMove, uint16_t yMove);
void absoluteMode(uint16_t* x, uint16_t* y, uint8_t* buffer, uint16_t colorUsed, struct tagBitMap8Bit* picture, uint16_t width);
void writeInPixelBuffer(uint16_t* x, uint16_t* y, uint8_t amount, uint8_t value, struct tagBitMap8Bit* picture, uint16_t width);

#endif
