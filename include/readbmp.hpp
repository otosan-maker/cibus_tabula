#ifndef __READ_BMP__
#define __READ_BMP__

#include "SPIFFS.h"

uint16_t read16(File f);
uint32_t read32(File f);

int drawBitmap_SD(const char *filename, int x, int y,uint8_t *framebuffer);

#endif