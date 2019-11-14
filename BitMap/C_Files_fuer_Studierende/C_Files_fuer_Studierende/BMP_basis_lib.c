//
//  BMP_basis_lib.c
//  GS_A3
//  Library of basis BMP functions
//  Created by Franz Korf on 31.10.19.
//  Copyright © 2019 Franz Korf. All rights reserved.
//

#include <stdio.h>
#include "BMP_basis_lib.h"

void printBITMAPFILEHEADER(BITMAPFILEHEADER  fileHeader) {
    printf("fileHeader.bfType         %u\n",   fileHeader.bfType);
    printf("fileHeader.bfSize         %u\n",   fileHeader.bfSize);
    printf("fileHeader.bfOffBits      %u\n",   fileHeader.bfOffBits);
    printf("\n");
}

void printBITMAPINFOHEADER(BITMAPINFOHEADER  bmpInfo) {
    printf("bmpInfo.biSize            %u\n",   bmpInfo.biSize);
    printf("bmpInfo.biWidth           %d\n",   bmpInfo.biWidth);
    printf("bmpInfo.biHeight          %d\n",   bmpInfo.biHeight);
    printf("bmpInfo.biPlanes          %u\n",   bmpInfo.biPlanes);
    printf("bmpInfo.biBitCount        %u\n",   bmpInfo.biBitCount);
    printf("bmpInfo.biCompression     %u\n",   bmpInfo.biCompression);
    printf("bmpInfo.biSizeImage       %u\n",   bmpInfo.biSizeImage);
    printf("bmpInfo.biXPelsPerMeter   %d\n",   bmpInfo.biXPelsPerMeter);
    printf("bmpInfo.biYPelsPerMeter   %d\n",   bmpInfo.biYPelsPerMeter);
    printf("bmpInfo.biClrUsed         %u\n",   bmpInfo.biClrUsed);
    printf("bmpInfo.biClrImportant    %u\n",   bmpInfo.biClrImportant);
    printf("\n");
}


bool basicChecks(BITMAPFILEHEADER  fileHeader, BITMAPINFOHEADER  bmpInfo) {
    if (fileHeader.bfType != BMP_SIGNATURE) {
        printf("basisChecks: wrong signature.\n");
        return false;
    }
    if (fileHeader.bfOffBits >= fileHeader.bfSize) {
        printf("basisChecks: bfOffBits points out of BMP file.\n");
        return false;
    }
    if (bmpInfo.biSize != sizeof(BITMAPINFOHEADER)) {
     printf("basisChecks: wrong biSize.\n");
     return false;
    }
    if (bmpInfo.biPlanes != 1) {
        printf("basisChecks: wrong biPlanes (must be 1).\n");
        return false;
    }
    if (bmpInfo.biHeight < 1) {
        printf("basisChecks: biHeight must be positive.\n");
        return false;
    }
    if (bmpInfo.biWidth < 1) {
        printf("basisChecks: biWidth must be positive.\n");
        return false;
    }
    if ((8 != bmpInfo.biBitCount) && (24 != bmpInfo.biBitCount)) {
        printf("basisChecks:  wrong biBitCount (must be 8 or 24).\n");
        return false;
    }
    if ((24 == bmpInfo.biBitCount) && (BI_RGB != bmpInfo.biCompression )) {
        printf("basisChecks: 24 bit format cannot be compressed.\n");
        return false;
    }
    if ((BI_RLE8 != bmpInfo.biCompression) && (BI_RGB != bmpInfo.biCompression )) {
        printf("basisChecks: unexpected compression format.\n");
        return false;
    }
    if (MAX_COLOR_TABLE_SIZE < bmpInfo.biClrUsed) {
        printf("basisChecks: biClrUsed out of range.\n");
        return false;
    }
    if ((24 == bmpInfo.biBitCount) && (bmpInfo.biClrUsed != 0)) {
        printf("basisChecks: biClrUsed must be 0 for 24 bit/pixel format.\n");
        return false;
    }
    return true;
}

// EOF
