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
	picture24Bit -> pixel = (struct tagRGBTriple ***) calloc(height * width, sizeof(struct tagRGBTriple));
		//Fehlerbehandlung
		if (NULL == picture24Bit -> pixel) {perror("Fehler bei der Speicherzuweisung! \n");}
		
	for (int i = 0; i < height; ++i) {
		picture24Bit->pixel[i] = (struct tagRGBTriple **) calloc (width, sizeof(struct tagRGBTriple));
			//Fehlerbehandlung
			if (NULL == picture24Bit -> pixel[i]) {perror("Fehler bei der Speicherzuweisung! \n");}
        
			
		for (int j = 0; j < width; ++j) {
			picture24Bit -> pixel[i][j] = (struct tagRGBTriple*) malloc (sizeof (struct tagRGBTriple)); 
				//Fehlerbehandlung
				if (NULL == picture24Bit -> pixel[i][j]) {perror("Fehler bei der Speicherzuweisung! \n");}
		}

	}
	 
    
	printf("Test0! \n");
	
	
	
        printf("Test1! \n");

    
 
        printf("Test2! \n");
        
    //Schreiben der RGB-Daten in die einzelnen Pixel   
    for (uint8_t j = 54; j < (54 + pixelCount * 3); j = j + 3) {
        for (uint32_t y = height - 1; y >= 0; y--) {
            for (uint32_t x = 0; x < width; x++) {		
                picture24Bit -> pixel[y][x] -> rgbBlue =    buffer[j];     printf("buffer b %d \n", buffer[j]);     
                picture24Bit -> pixel[y][x] -> rgbGreen =   buffer[j + 1]; printf("buffer g %d \n", buffer[j + 1]);
                picture24Bit -> pixel[y][x] -> rgbRed =     buffer[j + 2]; printf("buffer r %d \n", buffer[j + 2]);
               
            }
        }
            //result += fread(picture24Bit->pixel[i], 3, width, filePointer);
            
        
    }
    
    result += fread(picture24Bit->pixel, 3, 1 * width * height, filePointer);
    if (result != pixelCount*3)
    {
        printf("result: %d pixelCount: %d \n", result, pixelCount);
        perror("Fehler beim lesen der Bildpunkte");
        //return 1;
    }

    printf("size: %d \n", sizeof(picture24Bit->pixel[0][0]));
    //printf("Color pixel[0][0] = %x\n", picture24Bit->pixel[0][0]);
    uint8_t test = picture24Bit->pixel[0]->rgbBlue;
    printf("%d\n", test);
    printf("done! \n");

    //Freigeben des reservierten Heap-Speicherplatzes
    
    // free(picture24Bit -> pixel);
    
    // for (int i = 0; i < height; i++) {
    //     free(picture24Bit->pixel[i]);
	
        for (int j = 0; j < width; j++) {
            free(picture24Bit -> pixel[i][j]); 	
	}
    }
    
    return 0;
}





