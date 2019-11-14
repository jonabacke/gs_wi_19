//
// Created by jonathan on 13.11.19.
//

#include <stdio.h>
#include "stdint.h"
#include <malloc.h>
#include "build8BitStruct.h"
#include "general.h"
#include "expand.h"
#include "output.h"

uint8_t buildPalette(struct tagBitMap8Bit *picture8Bit, uint8_t *buffer) {

    uint16_t colorUsed = 0;

    if (picture8Bit -> infoHeader . biClrUsed == 0) {
        colorUsed = 256;
    } else {
        colorUsed = picture8Bit -> infoHeader.biClrUsed;
    }
    picture8Bit -> rgbPalette = (struct tagRGBQuad *) malloc(4 * colorUsed * sizeof(struct tagRGBQuad));

    for (int i = 0; i < colorUsed; ++i) {
        picture8Bit -> rgbPalette[i].rgbBlue        =   buffer[i * 4 + 0 + 54];
        picture8Bit -> rgbPalette[i].rgbGreen       =   buffer[i * 4 + 1 + 54];
        picture8Bit -> rgbPalette[i].rgbRed         =   buffer[i * 4 + 2 + 54];
        picture8Bit -> rgbPalette[i].rgbReserved    =   buffer[i * 4 + 3 + 54];
    }
    printf("buildPalette\n");

    return 0;
}

uint8_t buildPictureArray(struct tagBitMap8Bit *picture8Bit, uint8_t *buffer) {
    uint16_t width = 0;
    uint16_t height = 0;

    uint16_t colorUsed = 0;

    if (picture8Bit -> infoHeader . biClrUsed == 0) {
        colorUsed = 256;
    } else {
        colorUsed = picture8Bit -> infoHeader.biClrUsed;
    }
    printf("Hallo 1\n");

    width = picture8Bit -> infoHeader.biWidth + 4 - picture8Bit -> infoHeader.biWidth % 4;
    height = picture8Bit -> infoHeader.biHeight;

    picture8Bit -> pixel = (uint8_t **)malloc(width * height);
    for (int i = 0; i < height; ++i) {
        picture8Bit -> pixel[i] = (uint8_t*) malloc(width);
    }
    printf("Hallo 2\n");

    if (picture8Bit -> infoHeader.biCompression == 0) {
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                picture8Bit -> pixel [y][x] = buffer[54 + colorUsed + y * width + x];
            }
        }
    } else {
        uint16_t x = 0;
        uint16_t y = height;
        uint8_t isNotFinished = 1;
        while (isNotFinished) {
            if (buffer[54 + colorUsed + y * width + x] == 0) {
                switch (buffer[54 + colorUsed + y * width + x + 1]) {
                    case 0: endOfLine(&x, &y);
                        break;
                    case 1: endOfBitmap(&isNotFinished);
                        break;
                    case 2: deltaMove(&x, &y, buffer[54 + colorUsed + y * width + x + 2], buffer[54 + colorUsed + y * width + x + 3]);
                        break;
                    case 3: absoluteMode(&x, &y, buffer, colorUsed, picture8Bit, width);
                        break;
                    default: perror("Failure at expand");
                }
            } else {
                writeInPixelBuffer(&x, &y, buffer[54 + colorUsed + y * width + x], buffer[54 + colorUsed + y * width + x + 1], picture8Bit, width);
            }
        }
    }
    printf("buildPictureArray\n");
    return 0;

}
