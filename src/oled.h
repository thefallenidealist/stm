// created 141205
#ifndef OLED_H
#define OLED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c.h"

#define OLED_ADDR_W	0x78 // 0b1111000
//011110  SA0 R/W#

void oled_io_init(void);
uint32_t oled_init(void);
void oled_kocka(void);
void oled_example(void);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// OLED_H
