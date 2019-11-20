//
// Created by jonathan on 13.11.19.
//

#include "general.h"
#include "output.h"
#include <stdio.h>

void printBitMapFileHeader(struct tagBitMapFileHeader * fileHeader) {
    printf("--------------BitMapHeaderFile---------------\n");
    printf(" %x \t must be 4d42 \n", fileHeader -> bfType);
    printf(" %d \t bytes big \n", fileHeader -> bsSize);
    printf(" %d \t must be zero \n", fileHeader -> bfReserved1);
    printf(" %d \t must be zero \n", fileHeader -> bfReserved2);
    printf(" %d \t offset in bytes \n", fileHeader -> bfOfBits);
    printf("---------------------------------------------\n");
}

void printBitMapInfoHeader(struct tagBitMapInfoHeader * infoHeader) {
    printf("--------------BitMapHeaderInfo---------------\n");
    printf(" %d \t should be 40 \n", infoHeader -> biSize);
    printf(" %d \t width in pixel \n", infoHeader -> biWidth);
    printf(" %d \t height in pixel \n", infoHeader -> biHeight);
    printf(" %d \t must be 1 \n", infoHeader -> biPlanes);
    printf(" %d \t bits per Pixel \n", infoHeader -> biBitCount);
    printf(" %d \t 0: uncompressed; 1: compressed \n", infoHeader -> biCompression);
    printf(" %d \t Size of image (width * height wobei width durch 4 teilbar sein muss ) \n", infoHeader -> biSizeImage);
    printf(" %d \t pixelPerMeterX \n", infoHeader -> biXPelsPerMeter);
    printf(" %d \t pixelPerMeterY \n", infoHeader -> biYPelsPerMeter);
    printf(" %d \t number of colors \n", infoHeader -> biClrUsed);
    printf(" %d \t required number of colors \n", infoHeader -> biClrImportant);
    printf("---------------------------------------------\n");
}

void printBitMapColorPalette(struct tagBitMap8Bit *picture8Bit) {
    printf("-----------------BildPalette-----------------\n");

    int32_t colorUsed = 0;

    if (picture8Bit -> infoHeader . biClrUsed == 0) {
        colorUsed = 256;
    } else {
        colorUsed = picture8Bit -> infoHeader.biClrUsed;
    }
    for (int i = 0; i < colorUsed; ++i) {
        printf(" %d\t", i);
        printf(" %x\t", picture8Bit -> rgbPalette[i].rgbBlue);
        printf(" %x\t", picture8Bit -> rgbPalette[i].rgbGreen);
        printf(" %x\t", picture8Bit -> rgbPalette[i].rgbRed);
        printf(" %x\n", picture8Bit -> rgbPalette[i].rgbReserved);
    }
    printf("---------------------------------------------\n");
}

void printBitMap8BitPicture(struct tagBitMap8Bit *picture8Bit) {
    int32_t width = 0;
    if (picture8Bit->infoHeader.biWidth % 4 == 0){
        width = picture8Bit -> infoHeader.biWidth;
    } else {
        width = picture8Bit -> infoHeader.biWidth + 4 - picture8Bit -> infoHeader.biWidth % 4;
    }
    for (int32_t i = picture8Bit->infoHeader.biHeight - 1; i >= 0; i--) {
        for (int32_t j = 0; j < width; j++) {
            printf("%x \t", picture8Bit -> pixel[i][j]);
        }
        printf("\n");
    }
}

void printBitMap24BitPicture(struct tagBitMap24Bit *picture24Bit) {
    int32_t width = 0;
    if (picture24Bit->infoHeader.biWidth % 4 == 0){
        width = picture24Bit -> infoHeader.biWidth;
    } else {
        width = picture24Bit -> infoHeader.biWidth + 4 - picture24Bit -> infoHeader.biWidth % 4;
    }

    for (int32_t i = picture24Bit->infoHeader.biHeight - 1; i >= 0; i--) {
        for (int32_t j = 0; j < width; j++) {
            printf("%x \t", picture24Bit -> pixel[i][j]);
        }
        printf("\n");
    }
}

void printNewBitMapPicture(struct tagBitMap8Bit *picture24Bit) {
    uint8_t *buffer = NULL;
    int32_t bufferSize = (picture24Bit->infoHeader.biWidth * picture24Bit->infoHeader.biHeight * 3 + 54);
    buffer = (uint8_t*) malloc(bufferSize);
    buffer[0] = picture24Bit->fileHeader.bfType;
    buffer[1] = picture24Bit->fileHeader.bfType >> 8;
    buffer[2] = bufferSize;
    buffer[3] = bufferSize >> 8;
    buffer[4] = bufferSize >> 16;
    buffer[5] = bufferSize >> 24;
    buffer[6] = picture24Bit->fileHeader.bfReserved1;
    buffer[7] = picture24Bit->fileHeader.bfReserved1 >> 8;
    buffer[8] = picture24Bit->fileHeader.bfReserved2;
    buffer[9] = picture24Bit->fileHeader.bfReserved2 >> 8;
    buffer[10] = 54;
    buffer[11] = 0;
    buffer[12] = 0;
    buffer[13] = 0;
    buffer[14] = picture24Bit->infoHeader.biSize;
    buffer[15] = picture24Bit->infoHeader.biSize >> 8;
    buffer[16] = picture24Bit->infoHeader.biSize >> 16;
    buffer[17] = picture24Bit->infoHeader.biSize >> 24;
    buffer[18] = picture24Bit->infoHeader.biWidth;
    buffer[19] = picture24Bit->infoHeader.biWidth >> 8;
    buffer[20] = picture24Bit->infoHeader.biWidth >> 16;
    buffer[21] = picture24Bit->infoHeader.biWidth >> 24;
    buffer[22] = picture24Bit->infoHeader.biHeight;
    buffer[23] = picture24Bit->infoHeader.biHeight >> 8;
    buffer[24] = picture24Bit->infoHeader.biHeight >> 16;
    buffer[25] = picture24Bit->infoHeader.biHeight >> 24;
    buffer[26] = picture24Bit->infoHeader.biPlanes;
    buffer[27] = picture24Bit->infoHeader.biPlanes >> 8;
    buffer[28] = 24;
    buffer[29] = 0;
    buffer[30] = 0;
    buffer[31] = 0;
    buffer[32] = 0;
    buffer[33] = 0;
    buffer[34] = picture24Bit->infoHeader.biWidth * picture24Bit->infoHeader.biHeight;
    buffer[35] = picture24Bit->infoHeader.biWidth * picture24Bit->infoHeader.biHeight >> 8;
    buffer[36] = picture24Bit->infoHeader.biWidth * picture24Bit->infoHeader.biHeight >> 16;
    buffer[37] = picture24Bit->infoHeader.biWidth * picture24Bit->infoHeader.biHeight >> 24;
    buffer[38] = picture24Bit->infoHeader.biXPelsPerMeter;
    buffer[39] = picture24Bit->infoHeader.biXPelsPerMeter >> 8;
    buffer[40] = picture24Bit->infoHeader.biXPelsPerMeter >> 16;
    buffer[41] = picture24Bit->infoHeader.biXPelsPerMeter >> 24;
    buffer[42] = picture24Bit->infoHeader.biYPelsPerMeter;
    buffer[43] = picture24Bit->infoHeader.biYPelsPerMeter >> 8;
    buffer[44] = picture24Bit->infoHeader.biYPelsPerMeter >> 16;
    buffer[45] = picture24Bit->infoHeader.biYPelsPerMeter >> 24;
    buffer[46] = picture24Bit->infoHeader.biClrUsed;
    buffer[47] = picture24Bit->infoHeader.biClrUsed >> 8;
    buffer[48] = picture24Bit->infoHeader.biClrUsed >> 16;
    buffer[49] = picture24Bit->infoHeader.biClrUsed >> 24;
    buffer[50] = picture24Bit->infoHeader.biClrImportant;
    buffer[51] = picture24Bit->infoHeader.biClrImportant >> 8;
    buffer[52] = picture24Bit->infoHeader.biClrImportant >> 16;
    buffer[53] = picture24Bit->infoHeader.biClrImportant >> 24;
    int32_t i = 54;
        for (int j = picture24Bit->infoHeader.biHeight - 1; j >= 0; j--) {
            for (int k = 0; k < picture24Bit->infoHeader.biWidth; k++) {
                buffer[i] = picture24Bit->rgbPalette[picture24Bit->pixel[j][k]].rgbBlue;
                buffer[i + 1] = picture24Bit->rgbPalette[picture24Bit->pixel[j][k]].rgbGreen;
                buffer[i + 2] = picture24Bit->rgbPalette[picture24Bit->pixel[j][k]].rgbRed;
                i = i + 3;
                printf("i: %d \t j: %d \t k: %d \n", i, j, k);
            }

        }


    for (int i = 0; i < bufferSize; ++i) {
        printf("buffer: %x \n", buffer[i]);
    }
    FILE * filePointer;
    int32_t  result;
    filePointer = fopen("PictureCopy.bmp", "wb");
    result = fwrite(buffer, 1, bufferSize, filePointer);
    printf("Result %d \t BufferSize: %d \n", result, bufferSize);
    fclose(filePointer);


























}