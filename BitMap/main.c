/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#include <stdio.h>
#include "general.h"
#include "expand.h"
#include "buildStruct.h"
#include "output.h"
#include "analyse.h"

static struct tagBitMap8Bit *picture8Bit = NULL;
static struct tagBitMap24Bit *picture24Bit = NULL;



/*
* main-Methode
* @param int argc			Anzahl der beim Programmaufruf uebergebenen Argumente
* @param char **argv		Array mit den zu bearbeitenden Bilddatei-Pfaden
*/
int main(int argc, char **argv) {
  int8_t result = 0;
  int32_t resultSum = 0;
  for (int32_t i = 1; i < argc; i++)
  {

    printf("----------------Bild %2d----------------\n", i);
	
	
	picture8Bit = (struct tagBitMap8Bit*) malloc(sizeof(struct tagBitMap8Bit));
		//Fehlerbehandlung
		if (NULL == picture8Bit) {
			perror("Fehler bei der Speicherzuweisung! \n");
		}
	picture24Bit = (struct tagBitMap24Bit*) malloc(sizeof(struct tagBitMap24Bit));
		//Fehlerbehandlung
		if (NULL == picture24Bit) {
			perror("Fehler bei der Speicherzuweisung! \n");
		}


	/* Initialisiere Pointer */
	printf("%s\n", argv[i]);
	/* build struct */
	result = buildingStruct(argv[i], picture8Bit, picture24Bit);

	if (result != 0) {
      resultSum += 1;
      continue;
	}
	printf("%x\n", picture8Bit);


	/* print struct */
	if (picture8Bit -> fileHeader.bfType == 0x4d42) {
      //printBitMapFileHeader( &(picture8Bit->fileHeader));
      //printBitMapInfoHeader( &(picture8Bit->infoHeader));
      //printBitMapColorPalette(picture8Bit);
      //printBitMap8BitPicture(picture8Bit);
      getRect8Bit(picture8Bit);
      printNewBitMap8BitPicture(picture8Bit, argv[i]);
      for (int32_t j = 0; j < picture8Bit -> infoHeader.biHeight; j++) {
        free(picture8Bit->pixel[j]);
        picture8Bit -> pixel[j] = NULL;
      }
      free(picture8Bit->pixel);
      picture8Bit -> pixel = NULL;
      free(picture8Bit -> rgbPalette);
      picture8Bit -> rgbPalette = NULL;
      free(picture8Bit);
      picture8Bit = NULL;
	} 
	else if (picture24Bit -> fileHeader.bfType == 0x4d42) {
      printBitMapFileHeader( &(picture24Bit -> fileHeader));
      printBitMapInfoHeader( &(picture24Bit -> infoHeader));
      //printBitMap24BitPicture(picture24Bit);
      //getRect24Bit(picture24Bit);
      printNewBitMap24BitPicture(picture24Bit, argv[i]);


      for (int32_t i = 0; i < picture24Bit -> infoHeader.biHeight; i++) {
        free(picture24Bit -> pixel[i]);
        picture24Bit -> pixel[i] = NULL;
      }
      free(picture24Bit -> pixel);
      picture24Bit -> pixel = NULL;
      free(picture24Bit);
      picture24Bit = NULL;

	} 
	else {
    printf("Irgendwas ist bei diesem Bild schief gelaufen\n");
	}
  }
  return resultSum;
}





