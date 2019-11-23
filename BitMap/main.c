
#include <stdio.h>
#include "general.h"
#include "expand.h"
#include "buildStruct.h"
#include "output.h"
#include "analyse.h"

static struct tagBitMap8Bit *picture8Bit = NULL;
static struct tagBitMap24Bit *picture24Bit = NULL;

int main(int argc, char **argv) {
  int8_t result = 0;
  picture8Bit = (struct tagBitMap8Bit*) malloc(sizeof(struct tagBitMap8Bit));
  picture24Bit = (struct tagBitMap24Bit*) malloc(sizeof(struct tagBitMap24Bit));


  /* Initialisiere Pointer */
  printf("%s\n", argv[1]);
  /* build struct */
  result = buildingStruct(argv[1], picture8Bit, picture24Bit);

  if (result == 1) {
      return 1;
  }
  printf("%x\n", picture8Bit);


  /* print struct */
  if (picture8Bit != NULL) {
      printBitMapFileHeader( &(picture8Bit->fileHeader));
      printBitMapInfoHeader( &(picture8Bit->infoHeader));
      //printBitMapColorPalette(picture8Bit);
      //printBitMap8BitPicture(picture8Bit);
      //getRect(picture8Bit);
      printNewBitMapPicture(picture8Bit, argv[1]);
  } else if (picture24Bit != NULL) {
      printBitMapFileHeader( &(picture24Bit->fileHeader));
      printBitMapInfoHeader( &(picture24Bit->infoHeader));
      //printBitMap24BitPicture(picture24Bit);
  } else {
    printf("Irgendwas ist schief gelaufen\n");
  }

  /* analyse Struct */


















  return 0;
}
