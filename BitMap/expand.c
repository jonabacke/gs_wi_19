#include "expand.h"
#include "stdint.h"
#include <stdio.h>

void endOfLine(int32_t *x, int32_t *y) {
    *x = 0;
    *y = *y - 1;
    printf("endOfLine\n");

}

void endOfBitmap(int8_t *isNotFinished) {
    *isNotFinished = 0;
    printf("endOfBitmap\n");
}

void deltaMove(int32_t *x, int32_t *y, int32_t moveX, int32_t moveY) {
    *x = *x + moveX;
    *y = *y + moveY;
    printf("deltaMove\n");
}

void absoluteMode(int32_t * x, int32_t * y, uint8_t* buffer, int32_t colorUsed, struct tagBitMap8Bit* picture, int32_t width, int32_t *bufferPointer) {
    uint32_t offset = colorUsed + 54 + 2;
    while (buffer [offset + *bufferPointer] != 0) {
        picture -> pixel[*x][*y] = buffer[offset + *bufferPointer];
        *bufferPointer += 1;
        *x++;
        if (*x == width) {
            *x = 0;
            *y++;
        }
    }
    printf("absoluteMode\n");
}

void writeInPixelBuffer(int32_t * x, int32_t * y, uint8_t amount, uint8_t value, struct tagBitMap8Bit* picture, int32_t width) {
    while (amount > 0) {
        picture -> pixel[*y][*x] = value;
        *x = *x + 1;
        if (*x == width) {
            *x = 0;
            *y = *y - 1;
        }
        amount--;
    }
    printf("writeInPixelBuffer\n");
}
