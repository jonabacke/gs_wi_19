/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#ifndef BITMAP_BUILD8BITSTRUCT_H
#define BITMAP_BUILD8BITSTRUCT_H

#include <stdint.h>
#include "general.h"
#include <stdio.h>

uint8_t buildPalette(struct tagBitMap8Bit* picture8Bit, FILE* filePointer);

uint8_t buildPictureArray(struct tagBitMap8Bit *picture8Bit, FILE* filePointer);

#endif //BITMAP_BUILD8BITSTRUCT_H
