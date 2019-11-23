

#include "stdint.h"
#include "general.h"
#ifndef expand

#define expand


uint8_t endOfLine(int32_t * x, int32_t * y, struct tagBitMap8Bit *picture8Bit);
uint8_t endOfBitmap(int8_t*);
uint8_t deltaMove(int32_t * x, int32_t * y, int32_t xMove, int32_t yMove);
uint8_t absoluteMode(int32_t * x, int32_t * y, uint8_t* buffer, struct tagBitMap8Bit* picture, int32_t width, int32_t * bufferPointer);
uint8_t writeInPixelBuffer(int32_t * x, int32_t * y, uint8_t amount, uint8_t value, struct tagBitMap8Bit* picture, int32_t width);

#endif
