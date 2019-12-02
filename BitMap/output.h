/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#include "general.h"

#ifndef BITMAP_OUTPUT_H
#define BITMAP_OUTPUT_H


void printBitMapFileHeader(struct tagBitMapFileHeader * fileHeader);

void printBitMapInfoHeader(struct tagBitMapInfoHeader * fileHeader);

void printBitMapColorPalette(struct tagBitMap8Bit *picture8Bit);

void printBitMap8BitPicture(struct tagBitMap8Bit *picture8Bit);

void printBitMap24BitPicture(struct tagBitMap24Bit *picture24Bit);

void printNewBitMapPicture(struct tagBitMap8Bit *picture24Bit, uint8_t *fileNamePicture);

#endif //BITMAP_OUTPUT_H
