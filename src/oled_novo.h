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

typedef enum 
{
	OLED_MODE_HORIZONTAL_ADDRESSING = 0,
	OLED_MODE_VERTICAL_ADDRESSING	= 1,
	OLED_MODE_PAGE_ADDRESSING		= 2,	// default
	OLED_MODE_INVALID				= 3
} oled_mode_t;

void oled_io_init(void);
void oled_write_cmd(uint8_t cmd);
void oled_write_data(uint8_t data);
void oled_example(void);

void oled_init(void);
void oled_set_contrast(uint8_t contrast);
void oled_suspend(bool resume);
void oled_inverse(bool arg);


void oled_display_on(void);
void oled_display_off(void);
void oled_setXY(uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1);
void oled_set_mode(oled_mode_t mode);
oled_mode_t oled_get_mode(void);
void oled_set_column_lower(uint8_t column);
void oled_set_column_higher(uint8_t column);
void oled_set_column(uint8_t start, uint8_t end);
void oled_set_page(uint8_t start, uint8_t end);
void oled_set_page_start(uint8_t page);
void oled_bg(bool arg);



#ifdef __cplusplus
}
#endif	// __cplusplus
#endif	// OLED_H
