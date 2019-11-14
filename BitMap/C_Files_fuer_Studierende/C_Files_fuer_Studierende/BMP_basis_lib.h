//
//  BMP_basis_lib.h
//  GS_A3
//
//  Created by Franz Korf on 31.10.19.
//  Copyright © 2019 Franz Korf. All rights reserved.
//

#ifndef BMP_basis_lib_h
#define BMP_basis_lib_h

#include <stdbool.h>
#include "BMP_types.h"

/**
*********************************************************************
*  @brief This function prints a fileHeader structure to stdout.
*
*  @param fileHeader structure to be printed.
*
********************************************************************/
extern void printBITMAPFILEHEADER(BITMAPFILEHEADER  fileHeader);

/**
*********************************************************************
*  @brief This function prints a bitMapInfoHeader structure to stdout.
*
*  @param bmpInfo structure to be printed.
*
********************************************************************/
extern void printBITMAPINFOHEADER(BITMAPINFOHEADER  bmpInfo);

/**
*********************************************************************
*  @brief      This function checks basis properties of the
*              fileHeader and bitMapInfoHeader of BMP file.
*
*  @param      fileHeader fileHeader structure to be checked.
*
*  @param      bmpInfo bitMapInfoHeader structure to be checked.
*
*  @return     true <=> checks successful
********************************************************************/
extern bool basicChecks(BITMAPFILEHEADER  fileHeader, BITMAPINFOHEADER  bmpInfo);

#endif /* BMP_basis_lib_h */

// EOF
