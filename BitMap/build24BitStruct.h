/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



#include <stdint.h>
#include "general.h"
#ifndef BITMAP_BUILD24BITSTRUCT_H
#define BITMAP_BUILD24BITSTRUCT_H


uint8_t build24BitPictureArray(struct tagBitMap24Bit *picture24Bit, FILE *filePointer);

#endif //BITMAP_BUILD24BITSTRUCT_H
