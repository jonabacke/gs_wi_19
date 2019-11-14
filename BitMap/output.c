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
    printf(" %d \t pixelPerMeterX \n", infoHeader -> biXPelsPerPeter);
    printf(" %d \t pixelPerMeterY \n", infoHeader -> biYPelsPerMeter);
    printf(" %d \t number of colors \n", infoHeader -> biClrUsed);
    printf(" %d \t required number of colors \n", infoHeader -> biClrImportant);
    printf("---------------------------------------------\n");
}

void printBitMapColorPalette(struct tagBitMap8Bit *picture8Bit) {
    printf("-----------------BildPalette-----------------\n");
    for (int i = 0; i < picture8Bit -> infoHeader.biClrUsed; ++i) {
        printf(" %d\t", i);
        printf(" %x\t", picture8Bit -> rgbPalette[i].rgbBlue);
        printf(" %x\t", picture8Bit -> rgbPalette[i].rgbGreen);
        printf(" %x\t", picture8Bit -> rgbPalette[i].rgbRed);
        printf(" %x\n", picture8Bit -> rgbPalette[i].rgbReserved);
    }
    printf("---------------------------------------------\n");
}

void printBitMap8BitPicture(struct tagBitMap8Bit *picture8Bit) {
    uint32_t width = 0;
    width = picture8Bit -> infoHeader.biWidth + 4 - picture8Bit -> infoHeader.biWidth % 4;
    for (int i = picture8Bit->infoHeader.biHeight; i > 0; i--) {
        for (int j = 0; j < width; j++) {
            printf("%d \t", picture8Bit -> pixel[i][j]);
        }
        printf("\n");
    }
}

void printBitMap24BitPicture(struct tagBitMap24Bit *picture24Bit) {

}