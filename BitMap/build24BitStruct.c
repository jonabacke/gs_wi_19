//
// Created by jonathan on 13.11.19.
//

#include "build24BitStruct.h"
#include "stdint.h"
#include <stdio.h>
#include "general.h"
#include "output.h"
#include <malloc.h>

uint8_t build24BitPictureArray(struct tagBitMap24Bit *picture24Bit, uint8_t *buffer) {
/*
    //Bildhoehe und -breite aus infoHeader auslesen
    static int32_t width = 0;
    static int32_t height = 0;
    static int32_t bufferSize = 0;


    if (picture24Bit->infoHeader.biWidth % 4 == 0){
        width = picture24Bit -> infoHeader.biWidth;
    } else {
        width = picture24Bit -> infoHeader.biWidth + 4 - picture24Bit -> infoHeader.biWidth % 4;
    }
    height = picture24Bit -> infoHeader.biHeight;
    bufferSize = sizeof(buffer)-54; //54 Byte vom Header

    //Array vom Typ "struct tagRGBTriple" mit RGB-Werten aus dem Buffer fuellen
    struct tagRGBTriple picRGB[bufferSize/3];

    picture24Bit -> pixel = (tagRGBTriple **)malloc(buffersize/3);
    for (int i = 0; i < height; ++i) {
        picture24Bit -> pixel[i] = (uint8_t*) malloc(width);
    }

    for (int32_t i = 0, j = 0; i < bufferSize/3, j < bufferSize; i++, j + 3) {
        picRGB[i].rgbBlue = buffer[j];
        picRGB[i].rgbGreen = buffer[j+1];
        picRGB[i].rgbRed = buffer[j+2];
    }

    //picture24Bit (tagBitMap24Bit-struct) mit RGBTriple-Werten fuellen
    for (int32_t i; i < sizeof(picRGB); i++) {
        for (int32_t j = 0; j < height; j++) {
            for (int32_t k = 0; k - width; k++) {
                picture24Bit -> pixel[k][j] = picRGB[i];
            }
        }
    }
*/
    return 0;
}