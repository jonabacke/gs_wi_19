/*
 * BMP_types.h
 *
 *  Created on: 16.10.2016
 *      Author: Franz Korf
 */

#ifndef BMP_TYPES_H_
#define BMP_TYPES_H_

#include "MS_basetypes.h"

//
// types used within BMP files
//

#define BI_RGB	               0	     // uncompressed format
#define BI_RLE8	               1	     // compressed format
#define BMP_SIGNATURE          0x4d42
#define BI_RGB                 0
#define BI_RLE8                1
#define MAX_COLOR_TABLE_SIZE   256

typedef struct tagBITMAPFILEHEADER {
  WORD    bfType;
  DWORD   bfSize;
  WORD    bfReserved1;
  WORD    bfReserved2;
  DWORD   bfOffBits;
} __attribute__((__packed__)) BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
  DWORD  biSize;
  LONG   biWidth;
  LONG   biHeight;
  WORD   biPlanes;
  WORD   biBitCount;
  DWORD  biCompression;
  DWORD  biSizeImage;
  LONG   biXPelsPerMeter;
  LONG   biYPelsPerMeter;
  DWORD  biClrUsed;
  DWORD  biClrImportant;
} __attribute__((__packed__)) BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
  unsigned char    rgbBlue;
  unsigned char    rgbGreen;
  unsigned char    rgbRed;
  unsigned char    rgbReserved;
} __attribute__((__packed__)) RGBQUAD;

typedef struct tagRGBTRIPLE {
  unsigned char rgbtBlue;
  unsigned char rgbtGreen;
  unsigned char rgbtRed;
} __attribute__((__packed__)) RGBTRIPLE, *PRGBTRIPLE;

#define GREEN                           ((RGBTRIPLE) {0,   255, 0  })
#define RED                             ((RGBTRIPLE) {0,   0,   255})
#define BLUE                            ((RGBTRIPLE) {255, 0,   0  })

#endif /* BMP_TYPES_H_ */
