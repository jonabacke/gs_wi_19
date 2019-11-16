//
// Created by jonathan on 13.11.19.
//
#include "general.h"
#include "stdio.h"

#ifndef BITMAP_ANALYSE_H
#define BITMAP_ANALYSE_H

int32_t countRect(struct tagBitMap8Bit *picture8Bit);
void findRect(struct tagBitMap8Bit *picture8Bit, struct tagRect *rect);
void getColor(struct tagBitMap8Bit *picture8Bit, struct tagRect *rect);


#endif //BITMAP_ANALYSE_H
