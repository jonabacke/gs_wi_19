
#include <stdio.h>
#include "general.h"
#include "expand.h"
#include "buildStruct.h"
#include "output.h"


int main(int argc, char **argv) {

  /* Initialisiere Pointer */
  struct tagBitMap8Bit *picture8Bit = NULL;
  struct tagBitMap24Bit *picture24Bit = NULL;
  printf("%s", argv[1]);
  /* build struct */
  buildingStruct(argv[1], picture8Bit, picture24Bit);

  printf("%d\n", picture8Bit);
  /* print struct */
  if (picture8Bit != NULL) {
      printBitMapFileHeader( &(picture8Bit -> fileHeader));
      printBitMapInfoHeader( &(picture8Bit -> infoHeader));
      printBitMapColorPalette(picture8Bit);
      printBitMap8BitPicture(picture8Bit);
  } else if (picture24Bit != NULL) {
      printBitMapFileHeader( &(picture24Bit -> fileHeader));
      printBitMapInfoHeader( &(picture24Bit -> infoHeader));
      printBitMap24BitPicture(picture24Bit);
  } else {
    printf("Irgendwas ist schief gelaufen\n");



  }

  /* analyse Struct */


















  return 0;
}
