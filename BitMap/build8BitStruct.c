/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#include <stdio.h>
#include "stdint.h"
#include <malloc.h>
#include "build8BitStruct.h"
#include "general.h"
#include "expand.h"
#include "output.h"



/*
* Liest die Daten fuer die Farbpalette aus der Bilddatei und erstellt ein
* entsprechendes Struct (rgbPalette).
*
* @param struct tagBitMap8Bit *picture8Bit		Pointer auf Struct
* @param FILE *filePointer						filepointer
*/
uint8_t buildPalette(struct tagBitMap8Bit *picture8Bit, FILE *filePointer) {

    int32_t colorUsed = 0;
    int32_t result = 0;
	
	//Ermittlung der Anzahl der benutzten Farben
    if (picture8Bit -> infoHeader . biClrUsed == 0) {
        colorUsed = 256;
    } 
	else {
        colorUsed = picture8Bit -> infoHeader.biClrUsed;
    }
	
	//Reservieren von Heap-Speicher
    picture8Bit -> rgbPalette = (struct tagRGBQuad *) malloc( colorUsed * sizeof(struct tagRGBQuad));
	if (NULL == picture8Bit -> rgbPalette) {
		perror("Fehler bei der Speicherzuweisung! \n");
	}
	
	//Lesen der Farbpalette aus der Datei und Speichern in dem entsprechenden Struct
    result = fread(picture8Bit->rgbPalette, 1, colorUsed * 4, filePointer);
	
    if (result == colorUsed * 4) {
        printf("buildPalette ColorUsed: %d\n", colorUsed);
        return 0;
    } 
	else {
        printf("buildPaletteFailed\n");
        return 1;
    }
}



/*
* Liest eine 8-Bit Bilddatei ein und prueft, ob diese komprimiert ist. Wenn dies der Fall ist,
* wird sie zunaechst dekomprimiert und anschliessend, ansonsten werden direkt die Farbwerte in einem 
* Pixel-Array gespeichert.
*
* @param struct tagBitMap8Bit *picture8Bit		Pointer auf BildStruct
* @param FILE *filePointer						Pointer auf Bilddatei
*/
uint8_t buildPictureArray(struct tagBitMap8Bit *picture8Bit, FILE *filePointer) {
    int32_t width = 0;
    int32_t height = 0;
    int32_t offset = picture8Bit->fileHeader.bfOfBits;
	
	
	//Prueft, ob Bilddatei ein Padding aufweist
    if (picture8Bit -> infoHeader.biWidth % 4 == 0){
        width = picture8Bit -> infoHeader.biWidth;
    } 
	else {
        width = picture8Bit -> infoHeader.biWidth + 4 - picture8Bit -> infoHeader.biWidth % 4;
    }
	
	
    height = picture8Bit -> infoHeader.biHeight;
    printf(" width: %d \t", width);
    printf(" height: %d \n", height);
	
	
	//Reservieren von Heap-Speicher fuer Pixel-Array
    picture8Bit -> pixel = (uint8_t **)malloc(width * height);
    if (NULL == picture8Bit -> pixel) {
        perror("");
        return 1;
    }    
    for (int i = 0; i < height; ++i) {
        picture8Bit -> pixel[i] = (uint8_t*) malloc(width);
        if (NULL == picture8Bit -> pixel[i]) {
            perror("");
            return 1;
        }
    }

//Prueft, ob Bilddatei komprimiert ist und schreibt die Farbwerte in das Pixel-Array
	
	//Bilddatei ist nicht komprimiert und kann ohne groesseren Aufwand eingelesen werden
    if (picture8Bit -> infoHeader.biCompression == 0) {
        int32_t result = 0;
        for (int32_t i = 0; i < height; i++) {
            result = fread(picture8Bit -> pixel[i], 1, width, filePointer);

            if (result != width) {
                printf("buildPictureArrayUncompressedFailed\n");
                return 1;
            }
        }
        printf("buildPictureArrayUncompressed\n");
        return 0;

    } 
	// Bilddatei ist komprimiet und muss dekomprimiert werden bevor die Farbwerte im Pixel-Array gespeichert werden koennnen.
	else {
        uint8_t *buffer = (uint8_t *) malloc(picture8Bit->fileHeader.bsSize - offset);
        int32_t result = 0;
        int32_t x = 0;
        int32_t y = 0;
        int8_t isNotFinished = 1;
        int32_t bufferPointer = 0;
        uint8_t wordBoundary = 0;
		
        result = fread(buffer, 1, picture8Bit -> fileHeader.bsSize - offset, filePointer);
        if (result != picture8Bit -> fileHeader.bsSize - offset) {
            printf("result: %d \n", result);
            perror("buffer hat falsch gelesen");
            return 1;
        }
		// Solange  result == 0...
        result = 0;
        while (isNotFinished && bufferPointer < width * height) {
            if (buffer[bufferPointer] == 0) {
                switch (buffer[bufferPointer + 1]) {
                    case 0: 
                        result += endOfLine(&x, &y, picture8Bit);
                        bufferPointer += 2;
                        break;
                    case 1: 
                        result += endOfBitmap(&isNotFinished);
                        bufferPointer += 2;
                        break;
                    case 2: 
                        result += deltaMove(&x, &y, buffer[bufferPointer + 2], buffer[bufferPointer + 3]);
                        bufferPointer += 4;
                        break;
                    default: 
                        wordBoundary = (buffer[bufferPointer + 1] + 2) % 2; // 00 03 45 56 67 => 1; 00 04 45 56 67 45 => 0
                        result += absoluteMode(&x, &y, buffer, picture8Bit, width, &bufferPointer);                        
                        bufferPointer += wordBoundary;
                        break;
                }
                if (x > width || y > height || result > 0) {
                    printf("buildPictureArrayCompressedFailed x: %d y: %d result: %d\n", x, y, result);
                    return 1;
                }               
            } 
			else {
                result += writeInPixelBuffer(&x, &y, buffer[bufferPointer], buffer[bufferPointer + 1], picture8Bit, width);
                bufferPointer += 2;
                if (result != 0) {
                    printf("buildPictureArrayCompressedFailed x: %d y: %d result: %d\n", x, y, result);
                    return 1;
                }              
            }
            if (bufferPointer < 0) {
				perror("buildPictureArrayCompressedFailed\n");
				return 1;
            }
        }
        printf("buildPictureArrayCompressed\n");
    }
    return 0;
}



