/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#ifndef buildStruct
#define buildStruct

#include <stdint.h>
#include "general.h"
#include <stdio.h>

/**
 * @brief hier wird das Bild eingelesen und weiterverarbeitet
 * @param fileNamePicture name und Pfad zur Datei
 * @param picture8Bit 8BitPointer
 * @param picture24Bit 24BitPointer
 * */
uint8_t buildingStruct(uint8_t* fileNamePicture, struct tagBitMap8Bit*picture8Bit, struct tagBitMap24Bit*picture24Bit);

/**
 * @brief hier wird der fileheader aus der DAtei gelesen und in das BildStruct geschrieben
 * @param filePointer Filepointer zur DAtei wird übergeben
 * */
static uint8_t buildFileHeader(FILE*filePointer);


/**
 * @brief hier wird der infoheader aus der DAtei gelesen und in das BildStruct geschrieben
 * @param filePointer Filepointer zur DAtei wird übergeben
 * */
static uint8_t buildInfoHeader(FILE*filePointer);


#endif
