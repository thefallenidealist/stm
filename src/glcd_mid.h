#ifndef GLCD_MID_H
#define GLCD_MID_H

#include "delay.h"
#include "glcd_ili9341-cmd.h"
#include "glcd_low.h"

#define DELAY120 120

void glcd_sendCmd(uint8_t data);
void glcd_sendData(uint8_t data);
void glcd_sendData16(uint16_t data);
void glcd_ili9341_init();

#endif
