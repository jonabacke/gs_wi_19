//
// Created by jonathan on 13.11.19.
//
#include "general.h"
#include "stdio.h"

#ifndef BITMAP_ANALYSE_H
#define BITMAP_ANALYSE_H

int32_t getRect(struct tagBitMap8Bit *picture8Bit);
struct tagRectListElement* makeNewRect(struct tagBitMap8Bit *picture8Bit, int32_t x, int32_t y);
int8_t static isInRect(struct tagRectListElement *istHead, int32_t *x, int32_t y);
uint8_t static isRect(int32_t x, int32_t y, int32_t rectHeight, int32_t rectWidth, struct tagBitMap8Bit *picture8Bit);
uint8_t colorGreenRectToBlue(struct tagBitMap8Bit *picture8Bit);
#endif //BITMAP_ANALYSE_H
