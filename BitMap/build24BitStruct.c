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



/*
 * Ein Buffer uebertraegt Byteweise Bilddaten. Die ersten 56 Bytes bestehen aus Header-Informationen
 * und werden an dieser Stelle ignoriert. Die folgenden Bytes stellen die Farbinformationen fuer die
 * einzelnen Pixel des Bildes. Jeweils 3 aufeinander folgende Bytes stellen die Blau- Grün- und Rotwerte eines Pixels.
 * Jene werden jeweils in einem Struct gebuendelt und schließlich in einem Array, das die Bilddaten enthaelt gespeichert.
 *
 * @param   *picture24Bit   Zeiger auf das Bild
 * @param   *buffer         Zeiger auf den Buffer, der Byteweise die Bilddaten uebertraegt
 * */
uint8_t build24BitPictureArray(struct tagBitMap24Bit *picture24Bit, FILE *filePointer) {

    //Lokale Variablen
    int32_t width = 0;
    int32_t height = 0;
    int32_t offset = picture24Bit->fileHeader.bfOfBits;



    //Bildhoehe und -breite aus infoHeader auslesen
    if (picture24Bit->infoHeader.biWidth % 4 == 0) {
        width = picture24Bit->infoHeader.biWidth;
    } else {
        width = picture24Bit->infoHeader.biWidth + 4 - picture24Bit->infoHeader.biWidth % 4;
    }
    height = picture24Bit->infoHeader.biHeight;


    printf("24Bit-Bildhoehe: %dPixel\n", height);
    printf("24Bit-Bildbreite: %dPixel\n", width);
    printf("Anzahl der Bildpixel: %d\n", height * width);
    printf("tagRGBTripleSize %d Byte\n", sizeof(struct tagRGBTriple));



    //Reservieren von Heap-Speicher fuer das RGB-Triple-Array (pixelCount * 3 * Byte)
  /*  picture24Bit -> pixel[width * height] = (struct tagRGBTriple **) malloc(sizeof(struct tagRGBTriple) * (width * height));
    //Fehlerbehandlung
    if (NULL == picture24Bit -> pixel) {
        perror("Fehler bei der Speicherzuweisung! \n");
        return 1;
    }*/
        printf("TestA! \n");
    for (int i = 0; i < height; ++i) {
        picture24Bit->pixel[i] = (struct tagRGBTriple **) malloc(sizeof(struct tagRGBTriple) * 3 * width);
        //Fehlerbehandlung
        if (NULL == picture24Bit->pixel[i]) {
            perror("Fehler bei der Speicherzuweisung! \n");
            return 1;
        }



        for (int j = 0; j < width; ++j) {
            picture24Bit->pixel[i][j] = (struct tagRGBTriple *) malloc(sizeof(struct tagRGBTriple));
            //Fehlerbehandlung
            if (NULL == picture24Bit->pixel[i][j]) {
                perror("Fehler bei der Speicherzuweisung! \n");
                return 1;
            }
        }
    }




    printf("Test0! \n");
    printf("Test1! \n");
    printf("Test2! \n");


/*    for (uint32_t i = 0; i < height; i++){
        for (uint32_t j = 0; j < width; j++) {
            picture24Bit->pixel[i][j]->rgbBlue = fread(&picture24Bit->pixel[i][j]->rgbBlue, 1, 1, filePointer);
            picture24Bit->pixel[i][j]->rgbGreen = fread(&picture24Bit->pixel[i][j]->rgbGreen, 1, 1, filePointer);
            picture24Bit->pixel[i][j]->rgbRed = fread(&picture24Bit->pixel[i][j]->rgbRed, 1, 1, filePointer);
        }
    }*/


    for (uint32_t i = 0; i < height; i++){
        for (uint32_t j = 0; j < width; j++) {
            fread(&picture24Bit->pixel[i][j]->rgbBlue, 1, 1, filePointer);
            fread(&picture24Bit->pixel[i][j]->rgbGreen, 1, 1, filePointer);
            fread(&picture24Bit->pixel[i][j]->rgbRed, 1, 1, filePointer);
        }
    }





        printf("done! \n");



        //Bild oeffnen
        //system("C:\\TI_Labor\\github\\gs_wi_19\\BitMap\\testBilder\\testBilder\\640x480_24_bit_nicht_komprimiert_ohne_padding_bytes_blauer_rahmen2.bmp");

    //Freigeben des reservierten Heap-Speicherplatzes
    free(picture24Bit -> pixel);
    
    for (int i = 0; i < height; i++) {
        free(picture24Bit->pixel[i]);
	
        for (int j = 0; j < width; j++) {
            free(picture24Bit -> pixel[i][j]); 	
	    }
    }
    
    return 0;
}





