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

uint8_t buildingStruct(uint8_t*, struct tagBitMap8Bit*, struct tagBitMap24Bit*);

static uint8_t writeBuffer(uint8_t *, uint32_t);

static uint8_t buildFileHeader(FILE*);

static uint8_t buildInfoHeader(FILE*);


#endif
