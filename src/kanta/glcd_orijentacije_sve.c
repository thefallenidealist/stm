/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <propaliidealist@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Johnny Sorocil
 * ----------------------------------------------------------------------------
 */

//#define F_CPU 8000000	// Has to be here (not in .h or program.c) otherwise fucked up things happen
//#include <avr/io.h>
//#include <util/delay.h>
//#include <avr/pgmspace.h>
#include <stdlib.h>	// abs()
#include <string.h>	// strlen()
#include "font.c"
#include "glcd.h"
#include "ili9341cmd.h"

void glcd_sendCmd(unsigned char data)
{
	glcd_dc_low();
	glcd_cs_low();
	SPI1_send(data);
	glcd_cs_high();
}

void glcd_sendData(unsigned char data)
{
	glcd_dc_high();
	glcd_cs_low();
	SPI1_send(data);
	glcd_cs_high();
}

void glcd_sendData16(uint16_t data)
{
	unsigned char dataH = data >> 8;
	unsigned char dataL = data & 0xFF;
	glcd_dc_high();
	glcd_cs_low();
	//SPI_MasterTransmit(data1);
	//SPI_MasterTransmit(data2);
	SPI1_send(dataH);
	SPI1_send(dataL);
	glcd_cs_high();
}



//LCD settings
#define ILI9341_WIDTH 				240
#define ILI9341_HEIGHT				320
#define ILI9341_PIXEL				76800

//Colors
#define ILI9341_COLOR_WHITE			0xFFFF
#define ILI9341_COLOR_BLACK			0x0000
#define ILI9341_COLOR_RED			0xF800
#define ILI9341_COLOR_GREEN			0x07E0
#define ILI9341_COLOR_GREEN2		0xB723
#define ILI9341_COLOR_BLUE			0x001F
#define ILI9341_COLOR_BLUE2			0x051D
#define ILI9341_COLOR_YELLOW		0xFFE0
#define ILI9341_COLOR_ORANGE		0xFBE4
#define ILI9341_COLOR_CYAN			0x07FF
#define ILI9341_COLOR_MAGENTA		0xA254
#define ILI9341_COLOR_GRAY			0x7BEF //1111 0111 1101 1110
#define ILI9341_COLOR_BROWN			0xBBCA

//Commands
#define ILI9341_RESET				0x01
#define ILI9341_SLEEP_OUT			0x11
#define ILI9341_GAMMA				0x26
#define ILI9341_DISPLAY_OFF			0x28
#define ILI9341_DISPLAY_ON			0x29
#define ILI9341_COLUMN_ADDR			0x2A
#define ILI9341_PAGE_ADDR			0x2B
#define ILI9341_GRAM				0x2C
#define ILI9341_MAC					0x36
#define ILI9341_PIXEL_FORMAT		0x3A
#define ILI9341_WDB					0x51
#define ILI9341_WCD					0x53
#define ILI9341_RGB_INTERFACE		0xB0
#define ILI9341_FRC					0xB1
#define ILI9341_BPC					0xB5
#define ILI9341_DFC					0xB6
#define ILI9341_POWER1				0xC0
#define ILI9341_POWER2				0xC1
#define ILI9341_VCOM1				0xC5
#define ILI9341_VCOM2				0xC7
#define ILI9341_POWERA				0xCB
#define ILI9341_POWERB				0xCF
#define ILI9341_PGAMMA				0xE0
#define ILI9341_NGAMMA				0xE1
#define ILI9341_DTCA				0xE8
#define ILI9341_DTCB				0xEA
#define ILI9341_POWER_SEQ			0xED
#define ILI9341_3GAMMA_EN			0xF2
#define ILI9341_INTERFACE			0xF6
#define ILI9341_PRC					0xF7

/*
void glcd_init(void) 
{
	glcd_rst_on();
	
	glcd_sendCmd(ILI9341_RESET);
	delay_ms(2000);
	
	glcd_sendCmd(ILI9341_POWERA);
	glcd_sendData(0x39);
	glcd_sendData(0x2C);
	glcd_sendData(0x00);
	glcd_sendData(0x34);
	glcd_sendData(0x02);
	glcd_sendCmd(ILI9341_POWERB);
	glcd_sendData(0x00);
	glcd_sendData(0xC1);
	glcd_sendData(0x30);
	glcd_sendCmd(ILI9341_DTCA);
	glcd_sendData(0x85);
	glcd_sendData(0x00);
	glcd_sendData(0x78);
	glcd_sendCmd(ILI9341_DTCB);
	glcd_sendData(0x00);
	glcd_sendData(0x00);
	glcd_sendCmd(ILI9341_POWER_SEQ);
	glcd_sendData(0x64);
	glcd_sendData(0x03);
	glcd_sendData(0x12);
	glcd_sendData(0x81);
	glcd_sendCmd(ILI9341_PRC);
	glcd_sendData(0x20);
	glcd_sendCmd(ILI9341_POWER1);
	glcd_sendData(0x23);
	glcd_sendCmd(ILI9341_POWER2);
	glcd_sendData(0x10);
	glcd_sendCmd(ILI9341_VCOM1);
	glcd_sendData(0x3E);
	glcd_sendData(0x28);
	glcd_sendCmd(ILI9341_VCOM2);
	glcd_sendData(0x86);
	glcd_sendCmd(ILI9341_MAC);
	glcd_sendData(0x48);
	glcd_sendCmd(ILI9341_PIXEL_FORMAT);
	glcd_sendData(0x55);
	glcd_sendCmd(ILI9341_FRC);
	glcd_sendData(0x00);
	glcd_sendData(0x18);
	glcd_sendCmd(ILI9341_DFC);
	glcd_sendData(0x08);
	glcd_sendData(0x82);
	glcd_sendData(0x27);
	glcd_sendCmd(ILI9341_3GAMMA_EN);
	glcd_sendData(0x00);
	glcd_sendCmd(ILI9341_COLUMN_ADDR);
	glcd_sendData(0x00);
	glcd_sendData(0x00);
	glcd_sendData(0x00);
	glcd_sendData(0xEF);
	glcd_sendCmd(ILI9341_PAGE_ADDR);
	glcd_sendData(0x00);
	glcd_sendData(0x00);
	glcd_sendData(0x01);
	glcd_sendData(0x3F);
	glcd_sendCmd(ILI9341_GAMMA);
	glcd_sendData(0x01);
	glcd_sendCmd(ILI9341_PGAMMA);
	glcd_sendData(0x0F);
	glcd_sendData(0x31);
	glcd_sendData(0x2B);
	glcd_sendData(0x0C);
	glcd_sendData(0x0E);
	glcd_sendData(0x08);
	glcd_sendData(0x4E);
	glcd_sendData(0xF1);
	glcd_sendData(0x37);
	glcd_sendData(0x07);
	glcd_sendData(0x10);
	glcd_sendData(0x03);
	glcd_sendData(0x0E);
	glcd_sendData(0x09);
	glcd_sendData(0x00);
	glcd_sendCmd(ILI9341_NGAMMA);
	glcd_sendData(0x00);
	glcd_sendData(0x0E);
	glcd_sendData(0x14);
	glcd_sendData(0x03);
	glcd_sendData(0x11);
	glcd_sendData(0x07);
	glcd_sendData(0x31);
	glcd_sendData(0xC1);
	glcd_sendData(0x48);
	glcd_sendData(0x08);
	glcd_sendData(0x0F);
	glcd_sendData(0x0C);
	glcd_sendData(0x31);
	glcd_sendData(0x36);
	glcd_sendData(0x0F);
	glcd_sendCmd(ILI9341_SLEEP_OUT);

	delay_ms(1000);

	glcd_sendCmd(ILI9341_DISPLAY_ON);
	glcd_sendCmd(ILI9341_GRAM);
}
*/

   // moj init
void glcd_init(void)
{
	//SPI_MasterInit();
	glcd_cs_high();
	glcd_dc_high();

	glcd_rst_on();
	delay_ms(10);
	glcd_rst_off();

	glcd_setOrientation(P1);	// default

	glcd_sendCmd(ILI9341_CMD_POWER_ON_SEQ_CONTROL);
	glcd_sendData(ILI9341_CMD_IDLE_MODE_ON);
	glcd_sendData(ILI9341_CMD_MEMORY_WRITE);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_TEARING_EFFECT_LINE_OFF);
	glcd_sendData(0x02); 

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_B);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(ILI9341_CMD_PARTIAL_AREA);

	glcd_sendCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
	glcd_sendData(0x85);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(0x78);

	glcd_sendCmd(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(0xED);
	glcd_sendData(0x64);
	glcd_sendData(0x03);
	glcd_sendData(ILI9341_CMD_PARTIAL_MODE_ON);
	glcd_sendData(0X81);

	glcd_sendCmd(ILI9341_CMD_PUMP_RATIO_CONTROL);
	glcd_sendData(ILI9341_CMD_DISP_INVERSION_OFF);

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_1);
	glcd_sendData(0x23);	//VRH[5:0]

	glcd_sendCmd(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);
	//delay_ms(120);						// neka se nadje

	glcd_sendCmd(ILI9341_CMD_VCOM_CONTROL_1);
	glcd_sendData(ILI9341_CMD_READ_MEMORY_CONTINUE);
	glcd_sendData(ILI9341_CMD_DISPLAY_OFF);
	delay_ms(120);		// treba inace inicijalizira 2/3 ekrana

	glcd_sendCmd(ILI9341_CMD_VCOM_CONTROL_2);
	glcd_sendData(0x86);

	glcd_sendCmd(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_sendData(0x48);	//C8	//48 68gal.gal.gal.//28 E8 gal.gal.gal.	

	glcd_sendCmd(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
	glcd_sendData(ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS);

	glcd_sendCmd(ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(0x18); 

	glcd_sendCmd(ILI9341_CMD_DISPLAY_FUNCTION_CONTROL);
	glcd_sendData(0x08); 
	glcd_sendData(0x82);
	glcd_sendData(0x27);

	glcd_sendCmd(ILI9341_CMD_ENABLE_3_GAMMA_CONTROL);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(0x26);	//Gamma curve selected 	
	glcd_sendData(ILI9341_CMD_SOFTWARE_RESET);

	glcd_sendCmd(ILI9341_CMD_POSITIVE_GAMMA_CORRECTION);
	glcd_sendData(0x0F);
	glcd_sendData(0x31);
	glcd_sendData(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(0x08);
	glcd_sendData(0x4E);
	glcd_sendData(0xF1);
	glcd_sendData(ILI9341_CMD_VERT_SCROLL_START_ADDRESS);
	glcd_sendData(0x07);
	glcd_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);
	//delay_ms(120);						// neka se nadje
	glcd_sendData(0x03);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(ILI9341_CMD_READ_DISP_STATUS);
	glcd_sendData(ILI9341_CMD_NOP);

	glcd_sendCmd(ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION);
	glcd_sendData(ILI9341_CMD_NOP);
	glcd_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	glcd_sendData(0x14);
	glcd_sendData(0x03);
	glcd_sendData(ILI9341_CMD_SLEEP_OUT);
	delay_ms(120);						// neka se nadje
	glcd_sendData(0x07);
	glcd_sendData(0x31);
	glcd_sendData(ILI9341_CMD_POWER_CONTROL_2);
	glcd_sendData(0x48);
	glcd_sendData(0x08);
	glcd_sendData(0x0F);
	glcd_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	glcd_sendData(0x31);
	glcd_sendData(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	glcd_sendData(ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC);

	glcd_sendCmd(ILI9341_CMD_SLEEP_OUT);
	delay_ms(120); 	// nakon sleep outa treba 120 ms

	glcd_sendCmd(ILI9341_CMD_DISPLAY_ON);
	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
	//glcd_bg(bgcolor);
}

void glcd_setX(unsigned int x0, unsigned int x1)
{
	glcd_sendCmd(ILI9341_CMD_COLUMN_ADDRESS_SET);

	glcd_sendData16(x0);
	glcd_sendData16(x1);

	/*
	// ustedi na CS signalu
	// XXX ne ubrza nista
        glcd_dc_high();
        glcd_cs_low();
	//for(int i=0; i<length; i++)
	{
		SPI1_send(x0 >> 8);
		SPI1_send(x0 & 0xFF);
		SPI1_send(x1 >> 8);
		SPI1_send(x1 & 0xFF);
	}
        glcd_cs_high();
	*/
}

void glcd_setY(unsigned int y0,unsigned int y1)
{
	glcd_sendCmd(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_sendData16(y0);
	glcd_sendData16(y1);
	
	/*
	// ustedi na CS signalu
	// XXX ne ubrza nista
        glcd_dc_high();
        glcd_cs_low();
	//for(int i=0; i<length; i++)
	{
		SPI1_send(y0 >> 8);
		SPI1_send(y0 & 0xFF);
		SPI1_send(y1 >> 8);
		SPI1_send(y1 & 0xFF);
	}
        glcd_cs_high();
	*/
}

void glcd_setOrientation(char orientation)
{
	glcd_orientation = orientation;
	//if(glcd_orientation == PORTRAIT)
	if((glcd_orientation == PORTRAIT) || (glcd_orientation == P1) || (glcd_orientation == P2))
	{
		max_x = 240;
		max_y = 320;
	}
	//else if(glcd_orientation == LANDSCAPE)
	else if((glcd_orientation == LANDSCAPE) || (glcd_orientation == L1) || (glcd_orientation == L2))
	{
		max_x = 320;
		max_y = 240;
	}
}

//void glcd_setXY(unsigned int x0, unsigned int y0)
void glcd_setXY(unsigned int x0, unsigned int x1, unsigned int y0, unsigned y1)
// kao set page u koji ces pisat
{
	/*
	glcd_setX(x0, x0);
	glcd_setY(y0, y0);
	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
	*/
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
	//glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
}

void glcd_pixel(unsigned int x0, unsigned int y0, unsigned int color)
{
	/*
	if(glcd_orientation == PORTRAIT)
	{
		glcd_setXY(x0, y0);
		glcd_sendData16(color);
	}
	else if(glcd_orientation == LANDSCAPE)
	{
		glcd_setXY(y0, max_x-x0);
		glcd_sendData16(color);
	}
	*/
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
	for (;;)
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

void glcd_hline(unsigned int x0, unsigned int y0, unsigned int length, unsigned int color)
{
	/*
	if(glcd_orientation == PORTRAIT)
	{
		glcd_setX(x0,x0 + length);
		glcd_setY(y0,y0);
		glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
		int i=0;
		for(i=0; i<length; i++)
			glcd_sendData16(color);
	}
	else if (glcd_orientation ==  LANDSCAPE)
	{
		glcd_setX(y0, y0);
		glcd_setY(max_x-x0-length, max_x-x0);
		glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
		int i=0;
		for(i=0;i<length;i++)
			glcd_sendData16(color);
	}
	*/
	glcd_setXY(x0,x0+length,y0,y0);

	glcd_sendCmd(ILI9341_CMD_MEMORY_WRITE);
	int i=0;

	// ustedi na CS signalu
        glcd_dc_high();
        glcd_cs_low();
	for(i=0; i<length; i++)
	{
		//glcd_sendData16(color);
		SPI1_send(color >> 8);
		SPI1_send(color & 0xFF);
	}
        glcd_cs_high();
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
	// ustedi na CS signalu
        glcd_dc_high();
        glcd_cs_low();
	for(i=0; i<length; i++)
	{
		//glcd_sendData16(color);
		SPI1_send(color >> 8);
		SPI1_send(color & 0xFF);
	}
        glcd_cs_high();
}

void glcd_rectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color)
{
	glcd_hline(x0, y0, length, color);
	glcd_hline(x0, y0+width, length, color);
	glcd_vline(x0, y0, width, color);
	glcd_vline(x0+length, y0, width, color);
}

void glcd_fillRectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color)
{
	// TODO
	// dosta funkcija poziva ovo, probat ga ubrzat
	for(int i=0;i<width;i++)
	{
		glcd_hline(x0,y0+i,length,color);
	}
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

#define CHAR_X	6	// how many pixels is wide char
#define CHAR_Y	6	// how many pixels is wide char
#define CHAR_SPACE	2	// empty space beetween chars

void glcd_char(unsigned char ascii, unsigned int x, unsigned int y, unsigned int size, unsigned int fgcolor)	
{
	if( (ascii < 32) || (ascii > 126) )
	{
		// If not printable write red kocka
		glcd_fillRectangle(x, y, size*CHAR_X, size*CHAR_Y, red);
	}

	for (int i=0; i<FONT_X; i++)
	{

		//unsigned char temp = pgm_read_byte(&simpleFont[ascii-32][i]);	// because font.c starts at 0, not 32
		unsigned char temp = simpleFont[ascii-32][i];	// ARM

		for(int f=0; f<8; f++)
		{
			if((temp>>f) & 1)	// ako bit na trenutacnoj pozici = 1
			{
				// onda ga ispisi, pixel po pixel
				glcd_fillRectangle(x+i*size, y+f*size, size, size, fgcolor);
			}
			else
			{
				// bojaj u pozadinsku boju, "obrisi"
				glcd_fillRectangle(x+i*size, y+f*size, size, size, bgcolor);
			}
		}
	}
}

void glcd_string(char *string, unsigned int x, unsigned int y, unsigned int size, unsigned int fgcolor)
{
	while(*string)
	{
		glcd_char(*string, x, y, size, fgcolor);
		string++;

		if(x < MAX_X)
			x += FONT_SPACE*size;
	}
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

void glcd_clr(unsigned int x0, unsigned int y0, unsigned int size) 
{
	//glcd_fillRectangle(x0, y0, size*10, size*10, bgcolor);
	glcd_fillRectangle(x0, y0, size*8, size*8, bgcolor);
}

void glcd_clrLine(unsigned int y0, unsigned int size)
{
	glcd_fillRectangle(0, y0-size, max_x, size*10, bgcolor);
}

/*
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
*/

void glcd_bg(unsigned int color)
{
	//glcd_fillRectangle(0,0,max_x,max_y,color);
	glcd_fillRectangle(0,0,max_x,max_y+1,color);	// y+1 treba za P2 i L2 TODO
}

/*
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

void glcd_title(char *string, unsigned int size, unsigned int fgcolor, unsigned int bgcolor)
{
	unsigned int x0 = max_x/2 - (strlen(string)*size*FONT_SPACE)/2;
	unsigned int y0 = 0.5*size*FONT_SPACE;
	glcd_fillRectangle(0,0,max_x,2*size*FONT_SPACE,bgcolor);
	glcd_string(string,x0,y0,size,fgcolor);
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
