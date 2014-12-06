// glcd.h STM32

#include "glcd_colors.h"

#define GLCD_LED_PORT	GPIOB
#define GLCD_LED_PIN	GPIO_Pin_0	// PB0
#define GLCD_DC_PORT	GPIOB
//#define GLCD_DC_PIN	GPIO_Pin_1	// PB1
#define GLCD_DC_PIN	GPIO_Pin_8
#define GLCD_RESET_PORT GPIOB
#define GLCD_RESET_PIN	GPIO_Pin_9
#define GLCD_CS_PORT	GPIOB
#define GLCD_CS_PIN	GPIO_Pin_10	// PB10

#define MAX_X   239
#define MAX_Y   319

#define FONT_SPACE	6
#define FONT_X		8
#define FONT_Y		8

#define PORTRAIT	0
#define LANDSCAPE	1
#define P1		0
#define L1		1
#define P2		2
#define L2		3

unsigned int max_x, max_y;
unsigned int bgcolor = black;
//const unsigned char simpleFont[][8];
unsigned char glcd_orientation;

void glcd_sendCmd(unsigned char data);
void glcd_sendData(unsigned char data);
void glcd_sendData16(unsigned int data);
void glcd_init(void);
void glcd_setX(unsigned int x0,unsigned int x1);
void glcd_setY(unsigned int y0,unsigned int y1);
void glcd_setOrientation(char orientation);
//void glcd_setXY(unsigned int x0, unsigned int y0);
void glcd_line(unsigned int x0,unsigned int y0,unsigned int x1, unsigned int y1, unsigned int color);
void glcd_hline(unsigned int x0, unsigned int y0, unsigned int length, unsigned int color);
void glcd_vline(unsigned int x0, unsigned int y0, unsigned int length, unsigned int color);
void glcd_rectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color);
void glcd_fillRectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color);
void glcd_circle(int x0, int y0, int r, unsigned int color);
void glcd_fillCircle(int x0, int y0, int r, unsigned int color);
void glcd_char(unsigned char ascii, unsigned int x0, unsigned int y0,unsigned int size, unsigned int fgcolor);
void glcd_string(char *argstring, unsigned int x0, unsigned int y0, unsigned int size,unsigned int fgcolor);
unsigned char glcd_number(unsigned int long_num,unsigned int x0, unsigned int y0,unsigned int size,unsigned int fgcolor);
unsigned char glcd_float(float floatNumber, unsigned int x0, unsigned int y0, unsigned int size, unsigned int fgcolor);
void glcd_kocka(unsigned int x0, unsigned int y0, unsigned int koliko, unsigned int size, unsigned int fgcolor);
void glcd_clr(unsigned int x0, unsigned int y0, unsigned int size);
void glcd_clrLine(unsigned int y0, unsigned int size);
void glcd_pixel(unsigned int x0, unsigned int y0, unsigned int color);
void glcd_bar(unsigned int x0, unsigned int y0, unsigned int koliko, unsigned int bar_max, unsigned int size, unsigned int fgcolor, unsigned int rectangle_color);
void glcd_eq(char *string, unsigned int x0, unsigned int y0, float koliko, unsigned int size, unsigned int fgcolor, unsigned int rectangle_color);
void glcd_bg(unsigned int color);
void glcd_arc(int x, int y, int r, int startAngle, int endAngle, int thickness, unsigned int color);
void glcd_title(char *string, unsigned int size, unsigned int fgcolor, unsigned int bgcolor);
