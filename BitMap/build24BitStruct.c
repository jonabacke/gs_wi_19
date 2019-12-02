/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#include "buildStruct.h"
#include "build24BitStruct.h"
#include "stdint.h"
#include <stdio.h>
#include "general.h"
#include "output.h"
#include <malloc.h>



/*
 * Eine 24-Bit-Bilddatei besteht aus 56 Byte Header-Informationen, die an dieser Stelle ignoriert werden, da sie bereits
 * in dem buildStruct-Modul ausgelesen werden. Die darauf folgenden Bytes stellen die Farbinformationen fuer die
 * einzelnen Pixel des Bildes. Jeweils 3 aufeinander folgende Bytes stellen die Blau- Gruen- und Rotwerte eines Pixels.
 * Jene werden jeweils in einem Struct gebuendelt und schließlich in einem Pixel-Array, das die Farbwerte enthaelt gespeichert.
 *
 * @param 	struct tagBitMap24Bit *picture24Bit   	Zeiger auf das BildStruct
 * @param   FILE *filePointer         				Zeiger auf die eingelesene Bildatei
 * */
uint8_t build24BitPictureArray(struct tagBitMap24Bit *picture24Bit, FILE *filePointer) {

    //Lokale Variablen
    int32_t width = 0;
    int32_t height = 0;
    int32_t offset = picture24Bit->fileHeader.bfOfBits;
	int32_t pixelCount = 0;
	int32_t result = 0;

    //Bildhoehe und -breite aus infoHeader auslesen
    if (picture24Bit -> infoHeader.biWidth % 4 == 0) {
        width = picture24Bit -> infoHeader.biWidth;
    } 
	else {
        width = picture24Bit -> infoHeader.biWidth + 4 - picture24Bit -> infoHeader.biWidth % 4;
    }
    height = picture24Bit -> infoHeader.biHeight;
	
	pixelCount = width * height;



    printf("24Bit-Bildhoehe: %dPixel\n", height);
    printf("24Bit-Bildbreite: %dPixel\n", width);
    printf("Anzahl der Bildpixel: %d\n", height * width);
    printf("tagRGBTripleSize %d Byte\n", sizeof(struct tagRGBTriple));

   
   
    //Reservieren von Heap-Speicher fuer das RGB-Triple-Array (pixelCount * 3 * Byte)
	picture24Bit -> pixel = (struct tagRGBTriple **) calloc(height * width, sizeof(struct tagRGBTriple));
		//Fehlerbehandlung
		if (NULL == picture24Bit -> pixel) {
			perror("Fehler bei der Speicherzuweisung! \n");
		}
		
	for (int i = 0; i < height; ++i) {
		picture24Bit->pixel[i] = (struct tagRGBTriple *) calloc (width, sizeof(struct tagRGBTriple));
			//Fehlerbehandlung
			if (NULL == picture24Bit -> pixel[i]) {
				perror("Fehler bei der Speicherzuweisung! \n");
			}
	}
	  

	// Auslesen der Bilddatei und schreiben der RGB-Triple in das Pixel-Array 
    result = 0;
    for (size_t i = 0; i < height; i++) {
        result += fread(picture24Bit -> pixel[i], 3, width, filePointer);    
    }
    // Fehlerbehandlung
    if (result != pixelCount) {
        printf("result: %d pixelCount: %d \n", result, pixelCount);
        perror("Fehler beim lesen der Bildpunkte");
    }
    
    printf("done! \n");

    return 0;
}





