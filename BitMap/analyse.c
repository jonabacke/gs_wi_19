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
    listHead = (struct tagRectListElement*) malloc(sizeof(struct tagRectListElement));
    struct tagRectListElement *listPointer = NULL;
    listHead->next = NULL;

    int32_t amount = 0;
    width = 0;
    height = 0;
    uint8_t color = picture8Bit->pixel[0][0];

    width = picture8Bit -> infoHeader.biWidth;
    height = picture8Bit->infoHeader.biHeight;

    for (int32_t i = 0; i < height - 1; i++) {
        for (int32_t j = 0; j < width - 1; j++) {
            printf("\n");
            if (!isInRect(listHead, &j, i)) {
                printf("Color: %d \t x: %d \t y: %d \t Color(x,y): %d \n", color, j, i, picture8Bit->pixel[i][j]);
                color = picture8Bit->pixel[i][j];
                if (picture8Bit->pixel[i][j + 1] == color &&
                    picture8Bit->pixel[i + 1][j] == color &&
                    picture8Bit->pixel[i + 1][j + 1] == color) {
                    listPointer = listHead;
                    while (listPointer->next != NULL) {
                        listPointer = listPointer->next;
                    }
                    listPointer->next = makeNewRect(picture8Bit, j, i);
                    printf(" amount: %d \n", amount);
                    amount++;
                } else {
                    printf("Else-Block");
                    color = picture8Bit->pixel[i][j + 1];
                }
            }
        }
    }

    printf(" Anzahl: %d \n", amount);

    return amount;
}

int8_t isInRect(struct tagRectListElement *listHead, int32_t *x, int32_t y) {
    struct tagRectListElement *listPointer = listHead;
    while (listPointer->next != NULL) {
        listPointer = listPointer->next;
        printf("%d xPosition leftTop\n", listPointer->rect->position->topLeft[0]);
        if (*x >= listPointer->rect->position->topLeft[0] && *x <= listPointer->rect->position->topRight[0] &&
            y >= listPointer->rect->position->topRight[1] && y <= listPointer->rect->position->btmRight[1]) {
            *x = listPointer->rect->position->topRight[0];
            printf("newX: %d", *x);
            return 1;
        }
    }
    return 0;
}

struct tagRectListElement* makeNewRect(struct tagBitMap8Bit *picture8Bit, int32_t x, int32_t y) {
    struct tagRectListElement *listElement;
    listElement = (struct tagRectListElement*) malloc(sizeof(struct tagRectListElement));
    listElement->rect = (struct tagRect*) malloc(sizeof(struct tagRect));
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
    uint8_t color = picture8Bit->pixel[y][x];
    printf(" MakeNewRect1: Width: %d \t Height: %d \n", rectWidth, rectHeight);

    for (int32_t i = y; i < rectHeight; i++) {
        for (int32_t j = x; j < rectWidth; j++) {
            printf(" MakeNewRect: Color: %d \t x: %d \t y: %d \t Color(x,y): %d \n", color, j, i, picture8Bit->pixel[i][j]);

            if (color != picture8Bit->pixel[i][j] && i == y) {
                // i==y erste Zeile checken um die Breite herauszufinden
                rectWidth = j - 1;
            } else if (color != picture8Bit->pixel[i][j]) {

                rectHeight = i - 1;
            }
        }
    }
    printf(" MakeNewRect: Width: %d \t Height: %d \n", rectWidth, rectHeight);
    printf("%d,%d \t%d,%d \n%d,%d \t%d,%d\n", x,y, rectWidth,y,x,rectHeight,rectWidth,rectHeight);
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