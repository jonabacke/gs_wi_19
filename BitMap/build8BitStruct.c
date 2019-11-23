//
// Created by jonathan on 13.11.19.
//

#include <stdio.h>
#include "stdint.h"
#include <malloc.h>
#include "build8BitStruct.h"
#include "general.h"
#include "expand.h"
#include "output.h"

uint8_t buildPalette(struct tagBitMap8Bit *picture8Bit, FILE *filePointer) {

    int32_t colorUsed = 0;
    int32_t result = 0;

    if (picture8Bit -> infoHeader . biClrUsed == 0) {
        colorUsed = 256;
    } else {
        colorUsed = picture8Bit -> infoHeader.biClrUsed;
    }
    picture8Bit -> rgbPalette = (struct tagRGBQuad *) malloc( colorUsed * sizeof(struct tagRGBQuad));

    result = fread(picture8Bit->rgbPalette, 1, colorUsed * 4, filePointer);

    if (result == colorUsed * 4)
    {
        printf("buildPalette ColorUsed: %d\n", colorUsed);
        return 0;
    } else
    {
        printf("buildPaletteFailed\n");
        return 1;
    }
}

uint8_t buildPictureArray(struct tagBitMap8Bit *picture8Bit, FILE *filePointer) {
    int32_t width = 0;
    int32_t height = 0;
    int32_t offset = picture8Bit->fileHeader.bfOfBits;

    if (picture8Bit->infoHeader.biWidth % 4 == 0){
        width = picture8Bit -> infoHeader.biWidth;
    } else {
        width = picture8Bit -> infoHeader.biWidth + 4 - picture8Bit -> infoHeader.biWidth % 4;
    }
    height = picture8Bit -> infoHeader.biHeight;
    printf(" width: %d \t", width);
    printf(" height: %d \n", height);

    picture8Bit -> pixel = (uint8_t **)malloc(width * height);
    if (NULL == picture8Bit->pixel)
    {
        perror("");
        return 1;
    }    
    for (int i = 0; i < height; ++i) {
        picture8Bit -> pixel[i] = (uint8_t*) malloc(width);
        if (NULL == picture8Bit->pixel[i]) {
            perror("");
            return 1;
        }
    }

    if (picture8Bit -> infoHeader.biCompression == 0) {
        int32_t result = 0;
        for (int32_t i = 0; i < height; i++)
        {
            result = fread(picture8Bit->pixel[i], 1, width, filePointer);

            if (result != width)
            {
                printf("buildPictureArrayUncompressedFailed\n");
                return 1;
            }
        }
        printf("buildPictureArrayUncompressed\n");
        return 0;

    } else {
        uint8_t *buffer = (uint8_t *) malloc(picture8Bit->fileHeader.bsSize - offset);
        int32_t result = 0;
        int32_t x = 0;
        int32_t y = 0;
        int8_t isNotFinished = 1;
        int32_t bufferPointer = 0;
        result = fread(buffer, 1, picture8Bit->fileHeader.bsSize - offset, filePointer);
        if (result != picture8Bit->fileHeader.bsSize - offset)
        {
            return 1;
        }
        
        while (isNotFinished && bufferPointer < width * height) {
            printf("1:%d \t 2:%d \t %d \n", buffer[bufferPointer], buffer[bufferPointer + 1], bufferPointer);
            //printf("bufferPointer1: %d\n", bufferPointer);
            if (buffer[bufferPointer] == 0) {
                switch (buffer[bufferPointer + 1]) {
                    case 0: 
                        result = endOfLine(&x, &y, picture8Bit);
                        //printf("bufferPointer: %d \n", bufferPointer);
                        bufferPointer += 2;
                        if (result != 0)
                        {
                            bufferPointer = -1;
                        }
                        break;
                    case 1: 
                        result = endOfBitmap(&isNotFinished);
                        //printf("bufferPointer: %d \n", bufferPointer);
                        bufferPointer += 2;
                        if (result != 0)
                        {
                            bufferPointer = -1;
                        }
                        break;
                    case 2: 
                        result = deltaMove(&x, &y, buffer[bufferPointer + 2], buffer[bufferPointer + 3]);
                        //printf("bufferPointer: %d \n", bufferPointer);
                        bufferPointer += 4;
                        if (result != 0)
                        {
                            bufferPointer = -1;
                        }
                        break;
                    default: 
                        result = absoluteMode(&x, &y, buffer, picture8Bit, width, &bufferPointer);
                        //printf("bufferPointer: %d \n", bufferPointer);
                        if (result != 0)
                        {
                            bufferPointer = -1;
                        }
                        break;
                }
                if (x > width || y > height)
                {
                    printf("buildPictureArrayCompressedFailed\n");
                    return 1;
                }
                
            } else {
                //printf("bufferPointer: %d \n", bufferPointer);

                writeInPixelBuffer(&x, &y, buffer[bufferPointer], buffer[bufferPointer + 1], picture8Bit, width);
                bufferPointer += 2;
            }
            if (bufferPointer < 0) {
            printf("buildPictureArrayCompressedFailed\n");
            return 1;
            }
        }
        printf("buildPictureArrayCompressed\n");
    }
    return 0;

}

struct tagBitMap24Bit* concert8BitTo24Bit(struct tagBitMap8Bit bitMap8Bit) {
  /*
    struct tagBitMap24Bit *bitMap24Bit = NULL;
    bitMap24Bit = (struct tagBitMap24Bit*) malloc(sizeof(struct tagBitMap24Bit));
    bitMap24Bit -> fileHeader = (struct tagBitMapFileHeader*) malloc(sizeof(struct tagBitMapFileHeader));
    bitMap24Bit -> fileHeader = bitMap8Bit -> fileHeader;
    bitMap24Bit -> infoHeader = (struct tagBitMapInfoHeader*) malloc(sizeof(struct tagBitMapInfoHeader));
    bitMap24Bit -> infoHeader = bitMap8Bit -> infoHeader;


*/













}
