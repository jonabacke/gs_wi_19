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
    int8_t result = 0;
    fileHeader = (struct tagBitMapFileHeader *) malloc(sizeof(struct tagBitMapFileHeader));
    infoHeader = (struct tagBitMapInfoHeader *) malloc(sizeof(struct tagBitMapInfoHeader));
    buffer = (uint8_t* ) malloc(54);
    writeBuffer(fileNamePicture, 54);
    buildFileHeader();
    buildInfoHeader();
    free(buffer);
    buffer = NULL;
    buffer = (uint8_t*) malloc(fileHeader -> bsSize);
    result = writeBuffer(fileNamePicture, fileHeader -> bsSize);
    if (result == 1) {
        return 1;
    }
    if (infoHeader -> biBitCount == 8) {
        bitMap8Bit -> fileHeader = *fileHeader;
        bitMap8Bit -> infoHeader = *infoHeader;
        buildPalette(bitMap8Bit, buffer);
        buildPictureArray(bitMap8Bit, buffer);
    } else if (infoHeader -> biBitCount == 24) {
        bitMap24Bit -> fileHeader = *fileHeader;
        bitMap24Bit -> infoHeader = *infoHeader;
        build24BitPictureArray(bitMap24Bit, buffer);
    }
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

static uint8_t buildFileHeader() {
    fileHeader -> bfType = buffer[0] + buffer[1]*256;
    fileHeader -> bsSize = buffer[2] + buffer[3]*256 + buffer[4] * 65536 + buffer[5] * 16777216;
    fileHeader -> bfReserved1 = buffer[6] + buffer[7]*256;
    fileHeader -> bfReserved2 = buffer[8] + buffer[9]*256;
    fileHeader -> bfOfBits = buffer[10] + buffer[11]*256 + buffer[12] * 65536 + buffer[13] * 16777216;

    printf("buildFileHeader\n");
    return 0;
}

static uint8_t buildInfoHeader() {
    infoHeader -> biSize = buffer[14] + buffer[15]*256 + buffer[16] * 65536 + buffer[17] * 16777216;
    infoHeader -> biWidth = buffer[18] + buffer[19]*256 + buffer[20] * 65536 + buffer[21] * 16777216;
    infoHeader -> biHeight = buffer[22] + buffer[23]*256 + buffer[24] * 65536 + buffer[25] * 16777216;
    infoHeader -> biPlanes = buffer[26] + buffer[27]*256;
    infoHeader -> biBitCount = buffer[28] + buffer[29]*256;
    infoHeader -> biCompression = buffer[30] + buffer[31]*256 + buffer[32] * 65536 + buffer[33] * 16777216;
    infoHeader -> biSizeImage = buffer[34] + buffer[35]*256 + buffer[36] * 65536 + buffer[37] * 16777216;
    infoHeader -> biXPelsPerMeter = buffer[38] + buffer[39]*256 + buffer[40] * 65536 + buffer[41] * 16777216;
    infoHeader -> biYPelsPerMeter = buffer[42] + buffer[43]*256 + buffer[44] * 65536 + buffer[45] * 16777216;
    infoHeader -> biClrUsed = buffer[46] + buffer[47]*256 + buffer[48] * 65536 + buffer[49] * 16777216;
    infoHeader -> biClrImportant = buffer[50] + buffer[51]*256 + buffer[52] * 65536 + buffer[53] * 16777216;

    printf("buildInfoHeader\n");
    return 0;
}
