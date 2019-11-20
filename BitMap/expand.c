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
    *y = *y - moveY;
    printf("deltaMove\n");
}

void absoluteMode(int32_t * x, int32_t * y, uint8_t* buffer, struct tagBitMap8Bit* picture, int32_t width, int32_t *bufferPointer) {
    printf(" x:%d \t y:%d \t color%d  \n", *x, *y, picture->pixel[*y][*x]);
    while (buffer [*bufferPointer + 2] != 0) {
        picture -> pixel[*y][*x] = buffer[*bufferPointer + 2];
        *bufferPointer += 1;
            *x = *x + 1;
            if (*x >= width - 1) {
                *x = 0;
                *y = *y - 1;
            }
            printf(" x:%d \t y:%d \t color%d  \n", *x, *y, picture->pixel[*y][*x]);


    }
    *bufferPointer += 1;
    printf("absoluteMode\n");
}

void writeInPixelBuffer(int32_t * x, int32_t * y, uint8_t amount, uint8_t value, struct tagBitMap8Bit* picture, int32_t width) {
    while (amount > 0) {
       // printf("value: %d \t x:%d \t y:%d \t color%d \tamount: %d \n",value, *x, *y, picture->pixel[*y][*x], amount);
        picture -> pixel[*y][*x] = value;
       // printf("Hallo %d \n", width);
            *x = *x + 1;
        //    printf("Hallo \n");

            if (*x >= width) {
                *x = 0;
                *y = *y - 1;
            }

        //    printf("Value:%d \t x:%d \t y:%d \t color:%d \n", value, *x, *y, picture->pixel[*y][*x - 1]);



        amount--;
    }
    printf("writeInPixelBuffer\n");
}
