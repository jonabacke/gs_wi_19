

#include "stdint.h"
#include "general.h"
#ifndef expand

#define expand


void endOfLine(int32_t * x, int32_t * y);
void endOfBitmap(int8_t*);
void deltaMove(int32_t * x, int32_t * y, int32_t xMove, int32_t yMove);
void absoluteMode(int32_t * x, int32_t * y, uint8_t* buffer, int32_t colorUsed, struct tagBitMap8Bit* picture, int32_t width, int32_t * bufferPointer);
void writeInPixelBuffer(int32_t * x, int32_t * y, uint8_t amount, uint8_t value, struct tagBitMap8Bit* picture, int32_t width);

#endif
