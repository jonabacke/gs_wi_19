#include "expand.h"
#include "stdint.h"
#include <stdio.h>

void endOfLine(uint16_t *x, uint16_t *y) {
    *x = 0;
    *y = *y + 1;
    printf("endOfLine\n");

}

void endOfBitmap(uint8_t *isNotFinished) {
    *isNotFinished = 0;
    printf("endOfBitmap\n");
}

void deltaMove(uint16_t *x, uint16_t *y, uint16_t moveX, uint16_t moveY) {
    *x = *x + moveX;
    *y = *y + moveY;
    printf("deltaMove\n");
}

void absoluteMode(uint16_t* x, uint16_t* y, uint8_t* buffer, uint16_t colorUsed, struct tagBitMap8Bit* picture, uint16_t width) {
    uint32_t offset = colorUsed + 54 + 2;
    while (buffer [offset + *x + *y * width] != 0) {
        picture -> pixel[*x][*y] = buffer[offset + *x + *y];
        *x++;
        if (*x == width) {
            *x = 0;
            *y++;
        }
    }
    printf("absoluteMode\n");
}

void writeInPixelBuffer(uint16_t* x, uint16_t* y, uint8_t amount, uint8_t value, struct tagBitMap8Bit* picture, uint16_t width) {
    while (amount < 0) {
        picture -> pixel[*x][*y] = value;
        *x++;
        if (*x == width) {
            *x = 0;
            *y++;
        }
        amount--;
    }
    printf("writeInPixelBuffer\n");
}
