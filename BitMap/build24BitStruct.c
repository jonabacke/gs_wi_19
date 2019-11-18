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

static int32_t width = 0;
static int32_t height = 0;
static int32_t pixelCount = 0;



/*
 * Ein Buffer uebertraegt Byteweise Bilddaten. Die ersten 56 Bytes bestehen aus Header-Informationen
 * und werden an dieser Stelle ignoriert. Die folgenden Bytes stellen die Farbinformationen fuer die
 * einzelnen Pixel des Bildes. Jeweils 3 aufeinander folgende Bytes stellen die Blau- Grün- und Rotwerte eines Pixels.
 * Jene werden jeweils in einem Struct gebuendelt und schließlich in einem Array, das die Bilddaten enthaelt gespeichert.
 *
 * @param   *picture24Bit   Zeiger auf das Bild
 * @param   *buffer         Zeiger auf den Buffer, der Byteweise die Bilddaten uebertraegt
 * */
uint8_t build24BitPictureArray(struct tagBitMap24Bit *picture24Bit, uint8_t *buffer) {


    //Bildhoehe und -breite aus infoHeader auslesen
    if (picture24Bit->infoHeader.biWidth % 4 == 0){
        width = picture24Bit -> infoHeader.biWidth;
    } else {
        width = picture24Bit -> infoHeader.biWidth + 4 - picture24Bit -> infoHeader.biWidth % 4;
    }
    height = picture24Bit -> infoHeader.biHeight;

    pixelCount = width * height;

        printf("24Bit-Bildhoehe: %d\n", height);
        printf("24Bit-Bildbreite: %d\n", width);
        printf("Anzahl der Bildpixel: %d\n", pixelCount);



    //Array aus RGB-Structs (mit jeweils 3 8-Bit-Farbwerten)
    RGBTriple RGBArray[(pixelCount)];

        printf("sizeof(RGBArray): %d\n", sizeof(RGBArray)); // sizeof(RGBArray)=921600 Byte = pixelCount*3 //sizeof(RGBTriple)=3 Byte



    //Reservieren von Heap-Speicher fuer das RGB-Triple-Array (pixelCount * 3 * Byte)
    *picture24Bit -> pixel = (struct tagRGBTriple **) malloc(sizeof(RGBArray) * (sizeof(uint8_t)));

    // Fehlerbehandlung
    if (NULL == *picture24Bit -> pixel) {printf("Fehler bei der Speicherzuweisung! \n");}

        printf("Test1! \n");



    //Füllen des RGB-Structs mit den Bildwerten (ohne Header)
    for (int32_t i = 0, j = 0; i < (pixelCount), j < (54 + pixelCount * 3); i++, j = j + 3) {

        RGBArray[i].rgbBlue =  buffer[54 + j];          //printf("rgbBlue: %d\n", RGBArray[i].rgbBlue);
        RGBArray[i].rgbGreen = buffer[54 + j + 1];      //printf("rgbGreen: %d\n", RGBArray[i].rgbGreen);
        RGBArray[i].rgbRed =   buffer[54 + j + 2];      //printf("rgbRed: %d\n", RGBArray[i].rgbRed);
    }

        printf("Test2! \n");

    for (int32_t i=0; i < (pixelCount); i++) {
        for (int32_t y = height - 1; y >= 0; y--) {
            for (int32_t x = 0; x < width; x++) {
                *picture24Bit->pixel[y][x] = RGBArray[i];
            }
        }
    }


    printf("done! \n");

    //Freigeben des reservierten Heap-Speicherplatzes
    free(*picture24Bit -> pixel);
    return 0;
}





