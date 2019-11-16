//
// Created by jonathan on 13.11.19.
//

#include "analyse.h"
#include "general.h"
#include "stdio.h"

static int32_t width;
static int32_t height;

int32_t getRect(struct tagBitMap8Bit *picture8Bit) {
    struct tagRectListElement *listHead = NULL;
    struct tagRectListElement *listPointer = listHead;
    listHead->next = NULL;

    int32_t amount = 0;
    width = 0;
    height = 0;
    uint8_t color = picture8Bit->pixel[0][0];

    if (picture8Bit->infoHeader.biWidth % 4 == 0){
        width = picture8Bit -> infoHeader.biWidth;
    } else {
        width = picture8Bit -> infoHeader.biWidth + 4 - picture8Bit -> infoHeader.biWidth % 4;
    }

    height = picture8Bit->infoHeader.biHeight;

    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width - 1; ++j) {
            // TODO abfrage ob man innerhalb eines bereits gefundenen rects ist
            if (picture8Bit->pixel[j][i + 1] == color &&
                picture8Bit->pixel[j + 1][i] == color &&
                picture8Bit->pixel[j + 1][i + 1]) {
                while (listPointer->next != NULL) {
                    listPointer = listPointer->next;
                }
                listPointer->next = makeNewRect(picture8Bit, j, i);
                amount ++;
            } else {
                color = picture8Bit->pixel[i][j + 1];
            }
        }
    }

    return amount;
}

struct tagRectListElement* makeNewRect(struct tagBitMap8Bit *picture8Bit, int32_t x, int32_t y) {
    struct tagRectListElement *listElement;
    listElement = (struct tagRectListElement*) malloc(sizeof(struct tagRectListElement));
    listElement->rect = (struct tagRect*) malloc(sizeof(struct tagRect));
    listElement->next = NULL;
    listElement->rect->color = 0;
    listElement->rect->position = (struct tagPosition*) malloc(sizeof(struct tagPosition));
    listElement->rect->position->btmLeft[0] = 0;
    listElement->rect->position->btmLeft[1] = 0;
    listElement->rect->position->topLeft[0] = 0;
    listElement->rect->position->topLeft[1] = 0;
    listElement->rect->position->btmRight[0] = 0;
    listElement->rect->position->btmRight[1] = 0;
    listElement->rect->position->topRight[0] = 0;
    listElement->rect->position->topRight[1] = 0;
    listElement->rect->color = 0;
    listElement->rect->volume = 0;
    int32_t rectWidth = width;
    int32_t rectHeight = height;
    uint8_t color = picture8Bit->pixel[x][y];
    for (int i = y; i < rectHeight - 1; i++) {
        for (int j = x; j < rectWidth - 1; j++) {
            if (color != picture8Bit->pixel[j][i] && i == y) {
                rectWidth = j - 1;
            } else if (color != picture8Bit->pixel[j][i]) {
                rectHeight = i - 1;
            }
        }
    }
    listElement->rect->position->topLeft[0] = x;
    listElement->rect->position->topLeft[1] = y;
    listElement->rect->position->topRight[0] = rectWidth;
    listElement->rect->position->topRight[1] = y;
    listElement->rect->position->btmLeft[0] = x;
    listElement->rect->position->btmLeft[1] = rectHeight;
    listElement->rect->position->btmRight[0] = rectWidth;
    listElement->rect->position->btmRight[1] = rectHeight;
    listElement->rect->volume = (rectHeight - y) * (rectWidth - x);
    listElement->rect->color = color;
    listElement->next = NULL;
    return listElement;
}