// created 141205
#ifndef OLED_H
#define OLED_H

#include "i2c.h"

// wrong address from datasheet
//#define OLED_ADDR_W		0b0111100
//#define OLED_ADDR_R	0b0111101
#define OLED_ADDR_W	0x78 // 0b1111000
//011110  SA0 R/W#

void oled_io_init(void);
uint32_t oled_init(void);
void oled_kocka(void);
void oled_example(void);

#endif
