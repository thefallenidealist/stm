#ifndef GLCD_MID_H
#define GLCD_MID_H

#include "delay.h"
#include "glcd_ili9341-cmd.h"
#include "glcd_low.h"

#define DELAY120 120

typedef enum
{
	// datasheet v1.11, page 127
	// MY, MX, MV in 0x36 reg
	P1m = 0,
	L1  = 1,
	P1  = 2,
	L2m = 3,
	P2  = 4,
	L1m = 5,
	P2m = 6,
	L2  = 7
} glcd_orientation_t;

void glcd_writeCmd(uint8_t data);
void glcd_writeData(uint8_t data);
void glcd_writeData16(uint16_t data);
void glcd_ili9341_init(void);

int8_t glcd_set_hw_orientation(glcd_orientation_t orientation);


#endif
