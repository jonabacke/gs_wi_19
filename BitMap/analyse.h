//
// Created by jonathan on 13.11.19.
//
#include "general.h"
#include "stdio.h"

#ifndef BITMAP_ANALYSE_H
#define BITMAP_ANALYSE_H

int32_t getRect(struct tagBitMap8Bit *picture8Bit);
struct tagRectListElement* makeNewRect(struct tagBitMap8Bit *picture8Bit, int32_t , int32_t);


#endif //BITMAP_ANALYSE_H
