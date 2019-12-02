/*
* WS19_GSP
* @task		Aufgabe 3 - Bitmap
* @author	Jonathan Backes (Matr.-Nr. 2394482), Tobias Hardjowirogo (Matr.-Nr. 2387188)
* @date		2019/Nov-Dez
* @version	1
*/



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
    while (result > 0 && counter < 10){
        result = 0;
        filePointer = fopen(fileNamePicture, "r+b");
        result += buildFileHeader(filePointer);
        result +=  buildInfoHeader(filePointer);
        if (result > 0 || infoHeader->biHeight > 10000 || infoHeader->biWidth > 10000)
        {
            perror("buildheaderFailed");
        } else if (infoHeader -> biBitCount == 8) 
        {
            bitMap8Bit -> fileHeader = *fileHeader;
            bitMap8Bit -> infoHeader = *infoHeader;
            result += buildPalette(bitMap8Bit, filePointer);
            result += buildPictureArray(bitMap8Bit, filePointer);
        } else if (infoHeader -> biBitCount == 24) 
        {
            bitMap24Bit -> fileHeader = *fileHeader;
            bitMap24Bit -> infoHeader = *infoHeader;
            result += build24BitPictureArray(bitMap24Bit, filePointer);
            //printBitMapFileHeader( &(bitMap24Bit->fileHeader));
            //printBitMapInfoHeader( &(bitMap24Bit->infoHeader));
        }
        counter ++;
        fclose(filePointer);
    }
    if (result != 0)
    {
        perror("buildingStruct failed\n");
        return 1;
    } else
    {
        printf("buildingStruct result: %d\n", result);
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
