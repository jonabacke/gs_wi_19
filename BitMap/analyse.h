//
// Created by jonathan on 13.11.19.
//
#include "general.h"
#include "stdio.h"

#ifndef BITMAP_ANALYSE_H
#define BITMAP_ANALYSE_H

int32_t getRect(struct tagBitMap8Bit *picture8Bit);
struct tagRectListElement* makeNewRect(struct tagBitMap8Bit *picture8Bit, int32_t x, int32_t y);
int8_t isInRect(struct tagRectListElement *istHead, int32_t x, int32_t y);

#endif //BITMAP_ANALYSE_H
