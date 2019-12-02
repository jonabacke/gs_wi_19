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
uint8_t build24BitPictureArray(struct tagBitMap24Bit *picture24Bit, FILE *filePointer) {
    

    //Bildhoehe und -breite aus infoHeader auslesen
    if (picture24Bit->infoHeader.biWidth % 4 == 0){
        width = picture24Bit -> infoHeader.biWidth;
    } else {
        width = picture24Bit -> infoHeader.biWidth + 4 - picture24Bit -> infoHeader.biWidth % 4;
    }
    height = picture24Bit -> infoHeader.biHeight;

    
    //Anzahl der Pixel
    pixelCount = width * height;

    //for(uint8_t i = 0; i < 10000; i++){
    //printf("buffertest %d \n", buffer[i]);
    //}
    
        printf("24Bit-Bildhoehe: %d\n", height);
        printf("24Bit-Bildbreite: %d\n", width);
        printf("Anzahl der Bildpixel: %d\n", pixelCount);

    
      
	printf("tagRGBTripleSize %d\n", sizeof(struct tagRGBTriple));
        printf("pixel: %d\n", sizeof(struct tagRGBTriple) * width * height);
        printf("pixel[i]: %d\n", sizeof(struct tagRGBTriple) * width);
        printf("pixel[i][j]: %d\n", sizeof (struct tagRGBTriple));
        
        
    //Reservieren von Heap-Speicher fuer das RGB-Triple-Array (pixelCount * 3 * Byte)
	picture24Bit -> pixel = (struct tagRGBTriple ***) calloc(height * width, sizeof(struct tagRGBTriple));
		//Fehlerbehandlung
		if (NULL == picture24Bit -> pixel) {perror("Fehler bei der Speicherzuweisung! \n");}
		
	for (int i = 0; i < height; ++i) {
		picture24Bit->pixel[i] = (struct tagRGBTriple **) calloc (width, sizeof(struct tagRGBTriple));
			//Fehlerbehandlung
			if (NULL == picture24Bit -> pixel[i]) {perror("Fehler bei der Speicherzuweisung! \n");}
        
			
		// for (int j = 0; j < width; ++j) {
		// 	picture24Bit -> pixel[i][j] = (struct tagRGBTriple*) calloc (sizeof (struct tagRGBTriple)); 
		// 		//Fehlerbehandlung
		// 		if (NULL == picture24Bit -> pixel[i][j]) {perror("Fehler bei der Speicherzuweisung! \n");}
		// }
	}
    perror("malloc war erfolgreich");
    uint32_t result = 0;
    //Schreiben der RGB-Daten in die einzelnen Pixel   	
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
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

    printf("size: %d \n", sizeof(picture24Bit->pixel[0][0][0]));
    //printf("Color pixel[0][0] = %x\n", picture24Bit->pixel[0][0]);
    uint8_t test = picture24Bit->pixel[0][0]->rgbBlue;
    printf("%d\n", test);
    printf("done! \n");

    //Freigeben des reservierten Heap-Speicherplatzes
    
    // free(picture24Bit -> pixel);
    
    // for (int i = 0; i < height; i++) {
    //     free(picture24Bit->pixel[i]);
	
    //     for (int j = 0; j < width; j++) {
    //         free(picture24Bit -> pixel[i][j]); 	
	// }
    // }
    
    return 0;
}





