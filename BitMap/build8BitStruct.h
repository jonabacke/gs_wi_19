//
// Created by jonathan on 13.11.19.
//

#ifndef BITMAP_BUILD8BITSTRUCT_H
#define BITMAP_BUILD8BITSTRUCT_H

#include <stdint.h>
#include "general.h"
#include <stdio.h>

uint8_t buildPalette(struct tagBitMap8Bit* picture8Bit, FILE* filePointer);

uint8_t buildPictureArray(struct tagBitMap8Bit *picture8Bit, FILE* filePointer);

struct tagBitMap24Bit* concert8BitTo24Bit(struct tagBitMap8Bit bitMap8Bit);

#endif //BITMAP_BUILD8BITSTRUCT_H
