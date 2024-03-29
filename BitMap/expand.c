/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#include "expand.h"
#include "stdint.h"
#include <stdio.h>



uint8_t endOfLine(int32_t *x, int32_t *y, struct tagBitMap8Bit *picture8Bit) {
    *x = 0;
    *y = *y + 1;
    //printf("endOfLine\n");
    return 0;
}

uint8_t endOfBitmap(int8_t *isNotFinished) {
    *isNotFinished = 0;
    //printf("endOfBitmap\n");
    return 0;
}

uint8_t deltaMove(int32_t *x, int32_t *y, int32_t moveX, int32_t moveY) {
    *x = *x + moveX;
    *y = *y + moveY;
    //printf("deltaMove\n");
    return 0;
}

uint8_t absoluteMode(int32_t * x, int32_t * y, uint8_t* buffer, struct tagBitMap8Bit* picture, int32_t width, int32_t *bufferPointer) {
   // printf(" x:%d \t y:%d \t color%d  \n", *x, *y, picture->pixel[*y][*x]);
    uint8_t amount = buffer[*bufferPointer + 1];
    *bufferPointer += 2;
    while (amount > 0) {
        if (*y < picture->infoHeader.biHeight && *x < width) {
            picture -> pixel[*y][*x] = buffer[*bufferPointer];
        
            *bufferPointer += 1;
                *x = *x + 1;
                if (amount > 1) {
                    // if (*x >= width - 1)
                    // {
                    //     perror("reihe zu lang");
                    //     *x = 0;
                    //     *y = *y + 1;
                    // }
                }
            amount --;
        } 
        else {
            perror("absoluteModeFailed\n");
            return 1;
        }
    }
    return 0;
}

uint8_t writeInPixelBuffer(int32_t * x, int32_t * y, uint8_t amount, uint8_t value, struct tagBitMap8Bit* picture, int32_t width) {
    while (amount > 0 && *y < picture->infoHeader.biHeight && *x < width) {
            picture->pixel[*y][*x] = value;
            *x = *x + 1;
            if (amount > 1) {
                // if (*x > width - 1) 
                // {
                //     *x = 0;
                //     *y = *y + 1;
                //     perror("reihe zu lang");
                // }
            }
            amount--;
    }
    if (amount > 0) {
        perror("writeInPixelBufferFailed\n");
        return 1;
    } 
    else {
        return 0;
    }   
}
