
// glcd.h STM32

//#include "glcd_colors.h"

#define GLCD_LED_PORT	GPIOB
#define GLCD_LED_PIN	GPIO_Pin_0	// PB0
#define GLCD_DC_PORT	GPIOB
#define GLCD_DC_PIN	GPIO_Pin_1	// PB1
#define GLCD_RESET_PORT GPIOB
#define GLCD_RESET_PIN	GPIO_Pin_2	// PB2
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
// glcd_colors.h STM32

#define black	0x0000	// 
#define white	0xFFFF	// RGB
#define red	0xF800	// R
#define green	0x07E0	// G
#define blue	0x001F	// B
#define yellow	0xFFE0  // RG
#define cyan	0x07FF	// GB
#define purple	0xF81F	// RB
#define gray	0x0821	// 00001 000001 00001


unsigned int max_x=320, max_y=320;
unsigned int bgcolor = black;
//const unsigned char simpleFont[][8];
unsigned char glcd_orientation;

//Void glcd_sendCmd(unsigned char data);
void glcd_sendCmd(uint8_t data);
//void glcd_sendData(unsigned char data);
void glcd_sendData(uint8_t data);
void glcd_sendData16(uint16_t data);
//void glcd_sendData16(unsigned int data);
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


//glcd.c STM32

void glcd_cs_low()
{
	GPIO_ResetBits(GLCD_CS_PORT, GLCD_CS_PIN);
}

void glcd_cs_high()
{
	GPIO_SetBits(GLCD_CS_PORT, GLCD_CS_PIN);
}

void glcd_dc_low()
{
	GPIO_ResetBits(GLCD_DC_PORT, GLCD_DC_PIN);
}

void glcd_dc_high()
{
	GPIO_SetBits(GLCD_DC_PORT, GLCD_DC_PIN);
}

void glcd_led_off()
{
	GPIO_ResetBits(GLCD_LED_PORT, GLCD_LED_PIN);
}

void glcd_led_on()
{
	GPIO_SetBits(GLCD_LED_PORT, GLCD_LED_PIN);
}

void glcd_rst_off()
{
	// RESET = 1
	GPIO_SetBits(GLCD_RESET_PORT, GLCD_RESET_PIN);
}

void glcd_rst_on()
{
	// RESET = 0
	GPIO_ResetBits(GLCD_RESET_PORT, GLCD_RESET_PIN);
}



/*
  2012 Copyright (c) Seeed Technology Inc.
*/

//#include <avr/pgmspace.h>

//const unsigned char simpleFont[][8] PROGMEM=
const unsigned char simpleFont[][8] =
{	
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},	// 
  {0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},	// 
  {0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},	// 
  {0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},	// 
  {0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},	// 
  {0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},	// 
  {0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},	// 
  {0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},	// 
  {0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},	// 
  {0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},	// 
  {0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},	// 
  {0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},	// 
  {0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},	// 
  {0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},	// 
  {0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},	// 
  {0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},	// 
  {0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},	// 
  {0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},	// 
  {0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},	// 
  {0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},	// 
  {0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},	// 
  {0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},	// 
  {0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},	// 
  {0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},	// 
  {0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},	// 
  {0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},	// 
  {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},	// 
  {0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},	// 
  {0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},	// 
  {0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},	// 
  {0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},	// 
  {0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},	// 
  {0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},	// 
  {0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},	// 
  {0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},	// 
  {0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},	// 
  {0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},	// 
  {0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},	// 
  {0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},	// 
  {0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},	// 
  {0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},	// 
  {0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},	// 
  {0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},	// 
  {0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},	// 
  {0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},	// 
  {0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},	// 
  {0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},	// 
  {0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},	// 
  {0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},	// 
  {0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},	// 
  {0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},	// 
  {0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},	// 
  {0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},	// 
  {0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},	// 
  {0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},	// 
  {0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},	// 
  {0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},	// 
  {0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},	// 
  {0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},	// 
  {0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},	// 
  {0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},	// 
  {0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},	// 
  {0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},	// 
  {0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},	// 
  {0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},	// 
  {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},	// 
  {0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},	// 
  {0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},	// 
  {0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},	// 
  {0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},	// 
  {0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},	// 
  {0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},	// 
  {0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},	// 
  {0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},	// 
  {0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},	// 
  {0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},	// 
  {0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},	// 
  {0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},	// 
  {0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},	// 
  {0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},	// 
  {0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},	// 
  {0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},	// 
  {0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},	// 
  {0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},	// 
  {0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},	// 
  {0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},	// 
  {0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},	// 
  {0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},	// 
  {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},	// 
  {0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},	// 
  {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},	// 
  {0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},	// 
  {0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},	// 
  {0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},	// 
  {0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},	// 
  {0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00}, 	// 
  {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00}	// puna kocka
};


// glcd_ili9341.h

/* Level 1 Commands (from the display Datasheet) */
#define ILI9341_CMD_NOP					0x00
// 0x02
#define ILI9341_CMD_SOFTWARE_RESET			0x01
#define ILI9341_CMD_READ_DISP_ID			0x04
#define ILI9341_CMD_READ_DISP_STATUS			0x09
#define ILI9341_CMD_READ_DISP_POWER_MODE		0x0A
#define ILI9341_CMD_READ_DISP_MADCTRL			0x0B
#define ILI9341_CMD_READ_DISP_PIXEL_FORMAT		0x0C
#define ILI9341_CMD_READ_DISP_IMAGE_FORMAT		0x0D
#define ILI9341_CMD_READ_DISP_SIGNAL_MODE		0x0E
#define ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC		0x0F
#define ILI9341_CMD_ENTER_SLEEP_MODE			0x10
#define ILI9341_CMD_SLEEP_OUT				0x11
#define ILI9341_CMD_PARTIAL_MODE_ON			0x12
#define ILI9341_CMD_NORMAL_DISP_MODE_ON			0x13
#define ILI9341_CMD_DISP_INVERSION_OFF			0x20
#define ILI9341_CMD_DISP_INVERSION_ON			0x21
#define ILI9341_CMD_GAMMA_SET				0x26
#define ILI9341_CMD_DISPLAY_OFF				0x28
#define ILI9341_CMD_DISPLAY_ON				0x29
#define ILI9341_CMD_COLUMN_ADDRESS_SET			0x2A
#define ILI9341_CMD_PAGE_ADDRESS_SET			0x2B
#define ILI9341_CMD_MEMORY_WRITE			0x2C
#define ILI9341_CMD_COLOR_SET				0x2D
#define ILI9341_CMD_MEMORY_READ				0x2E
#define ILI9341_CMD_PARTIAL_AREA			0x30
#define ILI9341_CMD_VERT_SCROLL_DEFINITION		0x33
#define ILI9341_CMD_TEARING_EFFECT_LINE_OFF		0x34
#define ILI9341_CMD_TEARING_EFFECT_LINE_ON		0x35
#define ILI9341_CMD_MEMORY_ACCESS_CONTROL		0x36
#define ILI9341_CMD_VERT_SCROLL_START_ADDRESS		0x37
#define ILI9341_CMD_IDLE_MODE_OFF			0x38
#define ILI9341_CMD_IDLE_MODE_ON			0x39
#define ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET		0x3A
#define ILI9341_CMD_WRITE_MEMORY_CONTINUE		0x3C
#define ILI9341_CMD_READ_MEMORY_CONTINUE		0x3E
#define ILI9341_CMD_SET_TEAR_SCANLINE			0x44
#define ILI9341_CMD_GET_SCANLINE			0x45
#define ILI9341_CMD_WRITE_DISPLAY_BRIGHTNESS		0x51
#define ILI9341_CMD_READ_DISPLAY_BRIGHTNESS		0x52
#define ILI9341_CMD_WRITE_CTRL_DISPLAY			0x53
#define ILI9341_CMD_READ_CTRL_DISPLAY			0x54
#define ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS	0x55
#define ILI9341_CMD_READ_CONTENT_ADAPT_BRIGHTNESS	0x56
#define ILI9341_CMD_WRITE_MIN_CAB_LEVEL			0x5E
#define ILI9341_CMD_READ_MIN_CAB_LEVEL			0x5F
#define ILI9341_CMD_READ_ID1				0xDA
#define ILI9341_CMD_READ_ID2				0xDB
#define ILI9341_CMD_READ_ID3				0xDC
 
/* Level 2 Commands (from the display Datasheet) */
#define ILI9341_CMD_RGB_SIGNAL_CONTROL			0xB0
#define ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL		0xB1
#define ILI9341_CMD_FRAME_RATE_CONTROL_IDLE_8COLOR	0xB2
#define ILI9341_CMD_FRAME_RATE_CONTROL_PARTIAL		0xB3
#define ILI9341_CMD_DISPLAY_INVERSION_CONTROL		0xB4
#define ILI9341_CMD_BLANKING_PORCH_CONTROL		0xB5
#define ILI9341_CMD_DISPLAY_FUNCTION_CONTROL		0xB6
#define ILI9341_CMD_ENTRY_MODE_SET			0xB7
#define ILI9341_CMD_BACKLIGHT_CONTROL_1			0xB8
#define ILI9341_CMD_BACKLIGHT_CONTROL_2			0xB9
#define ILI9341_CMD_BACKLIGHT_CONTROL_3			0xBA
#define ILI9341_CMD_BACKLIGHT_CONTROL_4			0xBB
#define ILI9341_CMD_BACKLIGHT_CONTROL_5			0xBC
#define ILI9341_CMD_BACKLIGHT_CONTROL_6			0xBD
#define ILI9341_CMD_BACKLIGHT_CONTROL_7			0xBE
#define ILI9341_CMD_BACKLIGHT_CONTROL_8			0xBF
#define ILI9341_CMD_POWER_CONTROL_1			0xC0
#define ILI9341_CMD_POWER_CONTROL_2			0xC1
#define ILI9341_CMD_VCOM_CONTROL_1			0xC5
#define ILI9341_CMD_VCOM_CONTROL_2			0xC7
#define ILI9341_CMD_POWER_ON_SEQ_CONTROL		0xCB
#define ILI9341_CMD_POWER_CONTROL_A			0xCD
#define ILI9341_CMD_POWER_CONTROL_B			0xCF
#define ILI9341_CMD_NVMEM_WRITE				0xD0
#define ILI9341_CMD_NVMEM_PROTECTION_KEY		0xD1
#define ILI9341_CMD_NVMEM_STATUS_READ			0xD2
#define ILI9341_CMD_READ_ID4				0xD3
#define ILI9341_CMD_POSITIVE_GAMMA_CORRECTION		0xE0
#define ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION		0xE1
#define ILI9341_CMD_DIGITAL_GAMMA_CONTROL_1		0xE2
#define ILI9341_CMD_DIGITAL_GAMMA_CONTROL_2		0xE3
#define ILI9341_CMD_DRIVER_TIMING_CONTROL_A		0xE8
#define ILI9341_CMD_DRIVER_TIMING_CONTROL_B		0xEA
#define ILI9341_CMD_ENABLE_3_GAMMA_CONTROL		0xF2
#define ILI9341_CMD_INTERFACE_CONTROL			0xF6
#define ILI9341_CMD_PUMP_RATIO_CONTROL			0xF7


// glcd_low.c
#include "spi1_send.c"



// ako SPI salje 8b
void glcd_sendCmd(unsigned char data)
{
	glcd_dc_low();
	glcd_cs_low();
	SPI1_send(data);
	glcd_cs_high();
}
void glcd_sendData(uint8_t data)
{
	glcd_dc_high();
	glcd_cs_low();
	SPI1_send(data);
	glcd_cs_high();
}

void glcd_sendData16(uint16_t data)
//void glcd_sendData16(unsigned int data)
{
	unsigned char data1 = data>>8;		// manji je za 2^8 puta	// MSB dio prvo
	unsigned char data2 = data&0xff;	// pa LSB dio
	glcd_dc_high();
	glcd_cs_low();
	SPI1_send(data1);
	SPI1_send(data2);
	glcd_cs_high();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// 			16b SPI
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/*
void glcd_sendCmd(uint8_t data)
{
	glcd_dc_low();
	glcd_cs_low();
	SPI1_send(data);
	uint16_t data2 = data;
	SPI1_send(data2);
	glcd_cs_high();
}


//void glcd_sendData(unsigned char data)
void glcd_sendData(uint8_t data)
{
	glcd_dc_high();
	glcd_cs_low();
	SPI1_send(data);	// SPI 8b

	// little endian
	//uint16_t tmp = 0b1111111100000000;
	//uint16_t data2 = data + tmp;
	// big endian
	// 
	uint16_t tmp = 0b1111111100000000;
	uint16_t data2 = (data>>8) + tmp;
	//SPI1_send(data1);
	//SPI1_send(data2);

	//8b posalji kao 16b, ostatak su nule:
	//uint16_t data2 = data<<8;
	// 1010101000000000

	//8b posalji kao 16b, ostatak su jedinice
	//uint16_t data2 = (data<<8) + 255;
	// 1010101011111111

	//uint16_t data2 = data;
	//uint16_t data2 = data+65280;
//	uint16_t data2 = data + 1111111100000000;

	uint16_t data2 = data;
	SPI1_send(data2);

	glcd_cs_high();
}

void glcd_sendData16(uint16_t data)
//void glcd_sendData16(unsigned int data)
{
	// data = MSB___|__LSB
	unsigned char data1 = data>>8;	// manji je za 2^8 puta	// MSB dio prvo
	unsigned char data2 = data&0xff;
	glcd_dc_high();
	glcd_cs_low();
	SPI1_send(data1);
	SPI1_send(data2);
	glcd_cs_high();
}
*/

void glcd_init(void)
{
	//SPI_MasterInit();
	glcd_cs_high();
	glcd_dc_high();

	glcd_rst_on();
	delay_ms(10);
	glcd_rst_off();

	glcd_setOrientation(PORTRAIT);	// default

	glcd_sendCmd(ILI9341_CMD_POWER_ON_SEQ_CONTROL);
	glcd_sendData(ILI9341_CMD_IDLE_MODE_ON);
	glcd_sendData(ILI9341_CMD_MEMORY_WRITE);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_TEARING_EFFECT_LINE_OFF);
	glcd_sendData(0x02); 	// XXX 

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_B);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(ILI9341_CMD_PARTIAL_AREA);

	glcd_sendCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
	glcd_sendData(0x85); 	// XXX
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(0x78); 	// XXX

	glcd_sendCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(0xED);	// XXX
	glcd_sendData(0x64); 	// XXX
	glcd_sendData(0x03);	// XXX
	glcd_sendData(ILI9341_CMD_PARTIAL_MODE_ON);
	glcd_sendData(0X81); 	// XXX

	glcd_sendCmd(ILI9341_CMD_PUMP_RATIO_CONTROL);
	glcd_sendData(ILI9341_CMD_DISP_INVERSION_OFF);

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_1);
	glcd_sendData(0x23);	//VRH[5:0] 	// XXX

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);

	glcd_sendCmd(ILI9341_CMD_VCOM_CONTROL_1);
	glcd_sendData(ILI9341_CMD_READ_MEMORY_CONTINUE);
	glcd_sendData(ILI9341_CMD_DISPLAY_OFF);

	glcd_sendCmd(ILI9341_CMD_VCOM_CONTROL_2);
	glcd_sendData(0x86);	//--	// XXX

	glcd_sendCmd(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_sendData(0x48);	//C8	//48 68gal.gal.gal.//28 E8 gal.gal.gal.	// XXX

	glcd_sendCmd(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
	glcd_sendData(ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS);

	glcd_sendCmd(ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(0x18); 	// XXX

	glcd_sendCmd(ILI9341_CMD_DISPLAY_FUNCTION_CONTROL);
	glcd_sendData(0x08); 	// XXX
	glcd_sendData(0x82);	// XXX
	glcd_sendData(0x27);	// XXX

	glcd_sendCmd(ILI9341_CMD_ENABLE_3_GAMMA_CONTROL);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(0x26);	//Gamma curve selected 	// XXX
	glcd_sendData(ILI9341_CMD_SOFTWARE_RESET);

	glcd_sendCmd(ILI9341_CMD_POSITIVE_GAMMA_CORRECTION);
	glcd_sendData(0x0F); 	// XXX
	glcd_sendData(0x31);	// XXX
	glcd_sendData(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(0x08); 	// XXX
	glcd_sendData(0x4E); 	// XXX
	glcd_sendData(0xF1); 	// XXX
	glcd_sendData(ILI9341_CMD_VERT_SCROLL_START_ADDRESS);
	glcd_sendData(0x07); 	// XXX
	glcd_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);
	glcd_sendData(0x03);	// XXX
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(ILI9341_CMD_READ_DISP_STATUS);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(0x14); 	// XXX
	glcd_sendData(0x03);	// XXX
	glcd_sendData(ILI9341_CMD_SLEEP_OUT);
	glcd_sendData(0x07); 	// XXX
	glcd_sendData(0x31); 	// XXX
	glcd_sendData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(0x48); 	// XXX
	glcd_sendData(0x08); 	// XXX
	glcd_sendData(0x0F); 	// XXX
	glcd_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_sendData(0x31); 	// XXX
	glcd_sendData(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_sendData(ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC);

	glcd_sendCmd(ILI9341_CMD_SLEEP_OUT);
	delay_ms(120); 

	glcd_sendCmd(ILI9341_CMD_DISPLAY_ON);
	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
	glcd_bg(bgcolor);
}

void glcd_setX(unsigned int x0, unsigned int x1)
{
	glcd_sendCmd(ILI9341_CMD_COLUMN_ADDRESS_SET);
	glcd_sendData16(x0);
	glcd_sendData16(x1);
}

void glcd_setY(unsigned int y0,unsigned int y1)
{
	glcd_sendCmd(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_sendData16(y0);
	glcd_sendData16(y1);
}

void glcd_setOrientation(char orientation)
{
	glcd_orientation = orientation;
	if((glcd_orientation == PORTRAIT) || (glcd_orientation == P1) || (glcd_orientation == P2))
	{
		max_x = 240;
		max_y = 320;
	}
	else if((glcd_orientation == LANDSCAPE) || (glcd_orientation == L1) || (glcd_orientation == L2))
	{
		max_x = 320;
		max_y = 240;
	}
}

void glcd_setXY(unsigned int x0, unsigned int x1, unsigned int y0, unsigned y1)
{
	if(glcd_orientation == P1)
	{
		glcd_setX(x0, x1);
		glcd_setY(y0, y1);
	}
	else if(glcd_orientation == P2)
	{
		glcd_setX(max_x - x1, max_x - x0);
		glcd_setY(max_y - y1, max_y - y0);
	}
	else if(glcd_orientation == L1)
	{
		glcd_setX(y1, y0);
		glcd_setY(max_x-x1, max_x-x0);
	}
	else if(glcd_orientation == L2)
	{
		glcd_setX(max_y-y0, max_y-y1);
		glcd_setY(x0,x1);
	}
	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
}

/////////////////////////////////////////////////////////////////////////////////////////////// glcd_trio.c
void glcd_hline(unsigned int x0, unsigned int y0, unsigned int length, unsigned int color)
{
	glcd_setXY(x0,x0+length,y0,y0);

	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
	int i=0;
	for(i=0; i<length; i++)
		glcd_sendData16(color);
}

void glcd_vline(unsigned int x0, unsigned int y0, unsigned int length, unsigned int color)
{
	if((glcd_orientation == P1) || (glcd_orientation == P2))
	{
		glcd_setXY(x0,x0,y0,y0+length);
	}
	if((glcd_orientation == L1) || (glcd_orientation == L2))
	{
		glcd_setXY(x0,x0,y0+length,y0);
	}
	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
	int i=0;
	for(i=0; i<length; i++)
		glcd_sendData16(color);
}

void glcd_fillRectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color)
{
	for(int i=0;i<width;i++)
		glcd_hline(x0,y0+i,length,color);
}

void glcd_clr(unsigned int x0, unsigned int y0, unsigned int size) 	// XXX testirat
{
	glcd_fillRectangle(x0, y0, size*8, size*8, bgcolor);
}

void glcd_clrLine(unsigned int y0, unsigned int size)			// XXX testirat
{
	glcd_fillRectangle(0, y0-size, max_x, size*10, bgcolor);
}

void glcd_bg(unsigned int color)
{
	unsigned char oldOrientation = glcd_orientation;
	glcd_orientation = P1;	// ovako najbrze brise
	glcd_fillRectangle(0,0,240,320,color);
	//glcd_fillRectangle(0,0,max_x,max_y,color);
	glcd_orientation = oldOrientation;
}

void glcd_pixel(unsigned int x0, unsigned int y0, unsigned int color)
{
	glcd_setXY(x0,x0,y0,y0);
	glcd_sendData16(color);
}

/*
void glcd_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
	int x = x1-x0;
	int y = y1-y0;
	int dx = abs(x), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y), sy = y0<y1 ? 1 : -1;
	int err = dx+dy, e2;			// error value e_xy
	while(1)
	{
		glcd_pixel(x0,y0,color);
		e2 = 2*err;
		if (e2 >= dy)			// e_xy+e_x > 0
		{
			if (x0 == x1)
				break;
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)	 		// e_xy+e_y < 0
		{
			if (y0 == y1) break;
			err += dx;
			y0 += sy;
		}
	}
}
*/

void glcd_kockice(int size, int fgcolor2, int bgcolor2)
{
	glcd_bg(bgcolor2);

	for(int posX=0; posX < max_x;)
	{
		for(int posY=0; posY<max_y;)
		{
			// neparni stupac
			glcd_fillRectangle(posX,posY,size,size,fgcolor2);
			glcd_fillRectangle(posX,posY+=2*size,size,size,fgcolor2);
		}
		posX+=size;

		for(int posY=size; posY<max_y;)
		{
			// parni stupac
			glcd_fillRectangle(posX,posY,size,size,fgcolor2);
			glcd_fillRectangle(posX,posY+=2*size,size,size,fgcolor2);
		}
		posX+=size;
	}
}


/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <propaliidealist@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Johnny Sorocil
 * ----------------------------------------------------------------------------
 */

//#include "glcd_low.c"
#include <string.h> 	// strlen
//#include <stdio.h>
//#include "glcd_font.c" 	// novi
//#include "glcd_font2.c"

void glcd_char(unsigned char ascii, unsigned int x0, unsigned int y0, unsigned int size, unsigned int fgcolor)	
{
	if((ascii>=32)&&(ascii<=127))	// Characters below 32 are not printable, there are 127 of them
	{
		;	// If printable do nothing
	}	
	else
	{
		// If not printable write junk
		ascii = '?'-32;		// ascii = 63-32=31
	}
	//glcd_clr(x0, y0, size);	// delete before printing
	int i;
	for (i =0; i<FONT_X; i++ )
	{

		// pgm_read_byte - Read a byte from the program space with a 16-bit (near) address. 
		//unsigned char temp = pgm_read_byte(&simpleFont[ascii-32][i]);	// because font.c starts at 0, not 32
		unsigned char temp = simpleFont[ascii-32][i];	// ARM
		for(unsigned char f=0;f<8;f++)
		{
			if((temp>>f)&0x01)
				glcd_fillRectangle(x0+i*size, y0+f*size, size, size, fgcolor);
		}
	}
}

void glcd_string(char *string, unsigned int x0, unsigned int y0, unsigned int size, unsigned int fgcolor)
{
	while(*string)
	{
		//if((*string > 31) && (*string < 127))	// print only visible
		if((*string >= 32) && (*string <= 127))	// print only visible
		{
			glcd_char(*string, x0, y0, size, fgcolor);
		}
			string++;

		if(x0 < MAX_X)
			x0 += FONT_SPACE*size;
	}
}

void glcd_rectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color)
{
	glcd_hline(x0, y0, length, color);
	glcd_hline(x0, y0+width, length, color);
	glcd_vline(x0, y0, width, color);
	glcd_vline(x0+length, y0, width, color);
}

void glcd_circle(int x0, int y0, int r, unsigned int color)
{
	int x = -r, y = 0, err = 2-2*r, e2;
	do
	{
		glcd_pixel(x0-x, y0+y,color);
		glcd_pixel(x0+x, y0+y,color);
		glcd_pixel(x0+x, y0-y,color);
		glcd_pixel(x0-x, y0-y,color);
		e2 = err;
		if (e2 <= y)
		{
			err += ++y*2+1;
			if (-x == y && e2 <= x)
				e2 = 0;
		}
		if (e2 > x)
			err += ++x*2+1;
	} while (x <= 0);
}

void glcd_fillCircle(int x0, int y0, int r, unsigned int color)
{
	int x = -r, y = 0, err = 2-2*r, e2;
	do
	{
		glcd_vline(x0-x, y0-y, 2*y, color);
		glcd_vline(x0+x, y0-y, 2*y, color);

		e2 = err;
		if (e2 <= y)
		{
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x)
			err += ++x*2+1;
	} while (x <= 0);
}

unsigned char glcd_number(unsigned int long_num,unsigned int x0, unsigned int y0,unsigned int size,unsigned int fgcolor)
{
	unsigned char char_buffer[10] = "";
	unsigned char i = 0;
	unsigned char f = 0;

	if (long_num < 0)
	{
		f=1;
		glcd_char('-',x0, y0, size, fgcolor);
		long_num = -long_num;
			if(x0 < MAX_X)
				x0 += FONT_SPACE*size;
	}
	else if (long_num == 0)
	{
		f=1;
		glcd_char('0',x0, y0, size, fgcolor);
		return f;
			if(x0 < MAX_X)
				x0 += FONT_SPACE*size;
	}

	// XXX If number has multiple digits and is written trough loop then last digit has to be deleted manually before reset 

	while (long_num > 0)
	{
		char_buffer[i++] = long_num % 10;
		long_num /= 10;
	}

	f = f+i;
	for(; i > 0; i--)
	{
		//glcd_clr(x0,y0,size);
		glcd_char('0'+ char_buffer[i - 1],x0, y0, size, fgcolor);
			if(x0 < MAX_X)
				x0 += FONT_SPACE*size;
	}
	return f;
}

unsigned char glcd_float(float floatNumber, unsigned int x0, unsigned int y0, unsigned int size, unsigned int fgcolor)
{
	unsigned char decimal=1;
	unsigned int temp=0;
	float decy=0.0;
	float rounding = 0.5;
	unsigned char f=0;
	if(floatNumber<0.0)
	{
		glcd_char('-',x0, y0, size, fgcolor);
		floatNumber = -floatNumber;
		if(x0 < MAX_X)
			x0 += FONT_SPACE*size;
		f =1;
	}
	for (unsigned char i=0; i<decimal; ++i)
		rounding /= 10.0;
	floatNumber += rounding;

	temp = (unsigned int)floatNumber;
	unsigned char howlong=glcd_number(temp,x0, y0, size, fgcolor);
	f += howlong;
	if((x0+8*size*howlong) < MAX_X)
		x0+=FONT_SPACE*size*howlong;
	if(decimal>0)
	{
		glcd_char('.',x0, y0, size, fgcolor);
		if(x0 < MAX_X)
			x0 += FONT_SPACE*size;
		f +=1;
	}
	decy = floatNumber-temp;	// decimal part,
	for(unsigned char i=0;i<decimal;i++)
	{
		decy *=10;	// for the next decimal
		temp = decy;	// get the decimal
		glcd_number(temp,x0, y0, size, fgcolor);
		floatNumber = -floatNumber;
			if(x0 < MAX_X)
				x0 += FONT_SPACE*size;
		decy -= temp;
	}
	f += decimal;
	return f;
}

void glcd_kocka(unsigned int x0, unsigned int y0, unsigned int howmany, unsigned int size, unsigned int fgcolor)
{
	int j;
	for(j=0;j<howmany;j++)
	{
		int i;
		for (i =0; i<FONT_X; i++ )
		{
			//unsigned char temp = pgm_read_byte(&simpleFont[96][i]);	// kocka
			unsigned char temp = simpleFont[96][i];	// kocka
			unsigned char f=0;
			for(f=0;f<8;f++)
			{
				if((temp>>f)&0x01)
					glcd_fillRectangle(x0+i*size, y0+f*size, size, size, fgcolor);
			}
		}
		if(x0 < MAX_X)
			x0 += FONT_SPACE*size;
	}
}

void glcd_bar(unsigned int x0, unsigned int y0, unsigned int howmany, unsigned int bar_max, unsigned int size, unsigned int fgcolor, unsigned int rectangle_color)
{
	glcd_rectangle(x0, y0-size, FONT_SPACE*size*bar_max+size, FONT_Y*size+2*size-1, red);
	glcd_kocka(x0, y0, howmany, size, fgcolor);
}

void glcd_eq(char *string, unsigned int x0, unsigned int y0, float howmany, unsigned int size, unsigned int fgcolor, unsigned int rectangle_color)
{
	glcd_string(string,x0,y0,size,fgcolor);

	unsigned int bar_max = 10;	// Not for Soldano
	unsigned int duzina = strlen(string)*size*FONT_SPACE;
	unsigned int nx0 = x0 + duzina;	// Shift for the length of „string"
	//glcd_clr2(nx0,y0,10,size);
	glcd_bar(nx0, y0, howmany, bar_max, size, fgcolor, rectangle_color);

	unsigned int duzina2 = duzina + FONT_SPACE*size*bar_max+4*size;
	unsigned int nnx0 = x0 + duzina2;
	glcd_float(howmany,nnx0,y0,size,fgcolor);
}

/*
   //TODO sredit trigonometriju na ARM arhitekturi
void glcd_arc(int x, int y, int r, int startAngle, int endAngle, int thickness, unsigned int color)
{
        int rDelta = -(thickness/2);
        int px, py, cx, cy; 

        startAngle -= 90; 
        endAngle   -= 90; 
    
        if (startAngle!=endAngle)
        {   
                for (int i=0; i<thickness; i++)
                {   
                        px = x + cos((startAngle*3.14)/180) * (r+rDelta+i);
                        py = y + sin((startAngle*3.14)/180) * (r+rDelta+i);
                        for (int d=startAngle+1; d<endAngle+1; d++)
                        {   
                                cx = x + cos((d*3.14)/180) * (r+rDelta+i);
                                cy = y + sin((d*3.14)/180) * (r+rDelta+i);
				glcd_line(px, py, cx, cy, color);
                                px = cx; 
                                py = cy; 
                        }   
                }   
        }   
        else
        {   
                px = x + cos((startAngle*3.14)/180) * (r+rDelta);
                py = y + sin((startAngle*3.14)/180) * (r+rDelta);
                cx = x + cos((startAngle*3.14)/180) * (r-rDelta);
                cy = y + sin((startAngle*3.14)/180) * (r-rDelta);
		glcd_line(px, py, cx, cy, color);
        }   
}
*/

void glcd_title(char *string, unsigned int size, unsigned int fgcolor, unsigned int bgcolor)
{
	unsigned int x0 = max_x/2 - (strlen(string)*size*FONT_SPACE)/2;
	unsigned int y0 = 0.5*size*FONT_SPACE;
	glcd_fillRectangle(0,0,max_x,2*size*FONT_SPACE,bgcolor);	// treperi
	glcd_string(string,x0,y0,size,fgcolor);
}
