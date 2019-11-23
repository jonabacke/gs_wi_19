//
// Created by jonathan on 13.11.19.
//

#include "buildStruct.h"
#include <stdio.h>
#include "stdint.h"
#include "general.h"
#include "build8BitStruct.h"
#include "output.h"
#include "analyse.h"
#include "build24BitStruct.h"

static FILE *filePointer;
static uint8_t *buffer = NULL;
static struct tagBitMapFileHeader *fileHeader = NULL;
static struct tagBitMapInfoHeader *infoHeader = NULL;

uint8_t buildingStruct(uint8_t *fileNamePicture, struct tagBitMap8Bit* bitMap8Bit, struct tagBitMap24Bit* bitMap24Bit) {
    int8_t result = 1;
    int8_t counter = 0;
    fileHeader = (struct tagBitMapFileHeader *) malloc(sizeof(struct tagBitMapFileHeader));
    infoHeader = (struct tagBitMapInfoHeader *) malloc(sizeof(struct tagBitMapInfoHeader));
    // buffer = (uint8_t* ) malloc(54);
    // writeBuffer(fileNamePicture, 54);
    while (result > 0 && counter < 10){
        filePointer = fopen(fileNamePicture, "r+b");
        result += buildFileHeader(filePointer);
        result +=  buildInfoHeader(filePointer);
        if (infoHeader -> biBitCount == 8) {
            bitMap8Bit -> fileHeader = *fileHeader;
            bitMap8Bit -> infoHeader = *infoHeader;
            result += buildPalette(bitMap8Bit, filePointer);
            result += buildPictureArray(bitMap8Bit, filePointer);
        } else if (infoHeader -> biBitCount == 24) {
            bitMap24Bit -> fileHeader = *fileHeader;
            bitMap24Bit -> infoHeader = *infoHeader;
            //build24BitPictureArray(bitMap24Bit, buffer);
            printBitMapFileHeader( &(bitMap24Bit->fileHeader));
            printBitMapInfoHeader( &(bitMap24Bit->infoHeader));
        }
        counter ++;
        fclose(filePointer);
    }
    

    // free(buffer);
    // buffer = NULL;
    //buffer = (uint8_t*) malloc(fileHeader -> bsSize);
    //result = writeBuffer(fileNamePicture, fileHeader -> bsSize);
    //if (result == 1) {
    //    return 1;
    //}
    printf("buildingStruct\n");
    //countRect(bitMap8Bit);
    return 0;

}

static uint8_t writeBuffer(uint8_t *fileNamePicture, uint32_t size) {
    uint32_t i = 0;
    uint8_t counter = 0;
    uint8_t isRight = 0;

    while (!isRight && counter < 10) {
        filePointer = fopen(fileNamePicture, "r+b");
        i = fread(buffer, 1, size, filePointer);
        if (i != size) {
            perror("File was not read right");
            printf(" %d zu %d \n", size, i);
            fclose(filePointer);
            filePointer = NULL;
            counter ++;
        } else {
            isRight = 1;
        }
    }
    fclose(filePointer);
    printf("writeBuffer\n");

    if (!isRight && counter == 10) {
        return 1;
    } else {
        return 0;
    }

}

static uint8_t buildFileHeader(FILE *filePointer)  {
    int32_t result = 0;
    result = fread(fileHeader, 1, 14, filePointer);

    if (result == 14)
    {
        printf("buildFileHeader\n");
        return 0;
    } else
    {
        printf("buildFileHeaderFailed\n");
        return 1;
    }
}

static uint8_t buildInfoHeader(FILE *filePointer) {
    int32_t result = 0;
    result = fread(infoHeader, 1, 40, filePointer);

    printf("Size: %d \n", sizeof(*infoHeader));
    if (result == 40)
    {
        printf("buildInfoHeader\n");
        return 0;
    } else
    {
        printf("buildInfoHeaderFailed\n");
        return 1;
    }
    
    

}
