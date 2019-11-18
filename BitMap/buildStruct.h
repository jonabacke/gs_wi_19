//
// Created by jonathan on 13.11.19.
//

#ifndef buildStruct
#define buildStruct

#include <stdint.h>
#include "general.h"

uint8_t buildingStruct(uint8_t*, struct tagBitMap8Bit*, struct tagBitMap24Bit*);

static uint8_t writeBuffer(uint8_t *, uint32_t);

static uint8_t buildFileHeader();

static uint8_t buildInfoHeader();


#endif
