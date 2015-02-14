#ifndef GLCD_HIGH_H
#define GLCD_HIGH_H

#include <stdint.h>
#include "glcd_colors.h"
#include "glcd_mid.h"
#include "glcd_font.h"

#define CHAR_X	6	// how many pixels is wide char
#define CHAR_Y	6	// how many pixels is wide char
#define CHAR_SPACE	2	// empty space beetween chars

// prototipi
//void glcd_setOrientation(uint8_t orientation);
int8_t glcd_set_orientation(uint8_t orientation);
uint8_t glcd_get_orientation();
//void glcd_pixel(vuint16_t x0, vuint16_t y0, vuint16_t color);
void glcd_pixel(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t color);
void glcd_hline(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color);
void glcd_vline(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color);
//void glcd_fillRectangle(vuint16_t x0, vuint16_t y0, vuint16_t length, vuint16_t width, vuint16_t color);
//void glcd_fillRectangle(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t length, volatile uint16_t width, volatile uint16_t color);
void glcd_fillRectangle(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t length, volatile uint16_t height, volatile uint16_t color);
void glcd_bg(int color);
void glcd_char(unsigned char ascii, unsigned int x, unsigned int y, unsigned int size, unsigned int fgcolor);
//void glcd_string(char *string, unsigned int x, unsigned int y, unsigned int size, unsigned int fgcolor);
void glcd_string(const char *string, volatile uint16_t x, volatile uint16_t y, uint8_t size, uint16_t fgcolor);
uint8_t glcd_number(int32_t long_num, uint16_t x0, uint16_t y0, uint8_t size, uint16_t fgcolor);
void glcd_set_bgcolor(uint16_t color);
uint16_t glcd_get_bgcolor(void);
void glcd_test();
void glcd_speedtest();
void glcd_img_test();
void glcd_init();
void glcd_orientation_test();
int16_t glcd_get_width();
int16_t glcd_get_height();
const char *glcd_get_orientation_string();
void glcd_setXY(volatile uint16_t x0, volatile uint16_t x1, volatile uint16_t y0, volatile uint16_t y1);
void glcd_clear_line(volatile uint16_t x, volatile uint16_t y, uint8_t size);



#endif
