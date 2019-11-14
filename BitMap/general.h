#include <stdint.h>
#include <stdlib.h>

#ifndef general
#define general

typedef struct tagBitMapFileHeader {
  uint16_t bfType;          // Specifies the file type, must be BM (0x4d42)
  uint32_t bsSize;          // Specifies the size, in bytes, of the bitmap file.
  uint16_t bfReserved1;     // Reserved; must be zero.
  uint16_t bfReserved2;     // Reserved; must be zero.
  uint32_t bfOfBits;        // Specifies the offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits.
} bitMapFileHeader, *pBitMapFileHeader;


typedef struct tagBitMapInfoHeader {
  uint32_t  biSize;         // Specifies the number of bytes required by the structure (==40).
  int32_t   biWidth;        // Specifies the width of the bitmap, in pixels.
  int32_t   biHeight;        // Specifies the height of the bitmap, in pixels.
  uint16_t  biPlanes;       // Specifies the number of planes for the target device. This value must be set to 1.
  uint16_t  biBitCount;     // Specifies the number of bits-per-pixel. 8: 256 colors 24: 2^24 colors
  uint32_t  biCompression;  // Specifies the type of compression for a compressed bottomup bitmap BI_RGB: uncompressed BI_RLE8: compressed
  uint32_t  biSizeImage;    // Specifies the size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps.
  int32_t   biXPelsPerPeter;// Specifies the horizontal resolution, in pixels-per-meter, of the target device for the bitmap.
  int32_t   biYPelsPerMeter;// Specifies the vertical resolution, in pixels-per-meter, of the target device for the bitmap.
  uint32_t  biClrUsed;      // Specifies the number of color indexes in the color table that are actually used by the bitmap. 0 for max colors
  uint32_t  biClrImportant; // Specifies the number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required.
} bitMapInfoHeader, *pBitMapInfoHeader;


typedef struct tagRGBQuad {
  uint8_t rgbBlue;
  uint8_t rgbGreen;
  uint8_t rgbRed;
  uint8_t rgbReserved;
} RGBQuad;

typedef struct tagRGBQuad *colorPalette;

typedef struct tagRGBTriple {
  uint8_t rgbBlue;
  uint8_t rgbGreen;
  uint8_t rgbRed;
} RGBTriple;


typedef struct tagBitMap8Bit {
  struct tagBitMapFileHeader fileHeader;
  struct tagBitMapInfoHeader infoHeader;
  struct tagRGBQuad *rgbPalette;
  uint8_t **pixel;
} bitMap8Bit;


typedef struct tagBitMap24Bit {
  struct tagBitMapFileHeader fileHeader;
  struct tagBitMapInfoHeader infoHeader;
  struct tagRGBTrible *pixel[];
} bitMap24Bit;
#endif