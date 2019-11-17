//
// Created by jonathan on 13.11.19.
//
#include "buildStruct.h"
#include "build24BitStruct.h"
#include "stdint.h"
#include <stdio.h>
#include "general.h"
#include "output.h"
#include <malloc.h>

uint8_t build24BitPictureArray(struct tagBitMap24Bit *picture24Bit, uint8_t *buffer) {


    static int32_t width = 0;
    static int32_t height = 0;


    //Bildhoehe und -breite aus infoHeader auslesen
    if (picture24Bit->infoHeader.biWidth % 4 == 0){
        width = picture24Bit -> infoHeader.biWidth;
    } else {
        width = picture24Bit -> infoHeader.biWidth + 4 - picture24Bit -> infoHeader.biWidth % 4;
    }
    height = picture24Bit -> infoHeader.biHeight;


    printf("24Bit-Bildhoehe: %d\n", height);
    printf("24Bit-Bildbreite: %d\n", width);



    //Array aus RGB-Structs (mit jeweils 3 8-Bit-Farbwerten)
    struct tagRGBTriple pixelRGBArray[((width * height))];


    //Reservieren von Speicher (24Bit * Anzahl der Pixel) auf dem Heap
    *picture24Bit -> pixel = (struct tagRGBTriple **) malloc((width * height) * sizeof(struct tagRGBTriple) * 8);



    printf("Tach1! \n");


    //Füllen des RGB-Structs mit den Bildwerten (ohne Header)
    for (int32_t i = 0, j = 54; i < sizeof(pixelRGBArray), j < (width * height); i++, j++) {
        pixelRGBArray[i].rgbBlue = buffer[j];
        pixelRGBArray[i].rgbGreen = buffer[j + 1];
        pixelRGBArray[i].rgbRed = buffer[j + 2];
    }


    printf("Tach2! \n");


    //Speichern der RGB-Triple in den einzelnen Bildpixeln
    for (int32_t i=0; i < sizeof(pixelRGBArray); i++) {
        printf("Tach3! \n");
        for (int32_t j = 0; j < height; j++) {
            printf("Tach4! \n");
            for (int32_t k = 0; k - width; k++) {
                printf("Tach5! \n");
                *picture24Bit -> pixel[k][j] = (struct tagRGBTriple) pixelRGBArray[i];
                //printf("pixel %d: %d\n", i, pixelRGBArray[i]);
            }
        }
    }


    printf("done! \n");

    return 0;
}

