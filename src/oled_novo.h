// created 160509
#ifndef OLED_H
#define OLED_H

// SSD1306 OLED driver
// radi na 5V

#include "i2c.h"
#include "delay.h"

void oled_io_init(void);
void oled_write_cmd(uint8_t cmd);
void oled_write_data(uint8_t data);

#endif
