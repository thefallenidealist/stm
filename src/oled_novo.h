// created 160509
#ifndef OLED_H
#define OLED_H

#ifdef __cplusplus
extern "C" {
#endif

// SSD1306 OLED driver
// radi na 5V

#include "i2c.h"
#include "delay.h"

void oled_io_init(void);
void oled_write_cmd(uint8_t cmd);
void oled_write_data(uint8_t data);

#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// OLED_H
