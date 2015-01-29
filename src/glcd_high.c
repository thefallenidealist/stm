#include "glcd_high.h"
//#include "src/img.bmp.c"

// 150116	vraceno na "sporije" verzije, ali se postuje layerizacija
//		"brze" verzije dobiju max 1 ms na -O2 ili -O3 (jednako brzo radi);

static unsigned int max_x, max_y;
static unsigned int bgcolor = black;
static unsigned char glcd_orientation;

// XXX font mora bit ovdje, a ne u svom .h fajlu

//#ifndef GLCD_FONT_H
//#define GLCD_FONT_H

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

//#endif


//void glcd_setOrientation(char orientation)
void glcd_setOrientation(uint8_t orientation)
{
	glcd_orientation = orientation;

	if ((glcd_orientation == PORTRAIT) || (glcd_orientation == P1) || (glcd_orientation == P2))
	{
		/*
		max_x = 239;
		max_y = 319;
		*/
		max_x = 240;
		max_y = 320;
	}
	else if ((glcd_orientation == LANDSCAPE) || (glcd_orientation == L1) || (glcd_orientation == L2))
	{
		/*
		max_x = 319;
		max_y = 239;
		*/
		max_x = 320;
		max_y = 240;
	}
}

//static void glcd_setX(uint16_t x0, uint16_t x1)
static void glcd_setX(volatile uint16_t x0, volatile uint16_t x1)
{
	glcd_writeCmd(ILI9341_CMD_COLUMN_ADDRESS_SET);

	glcd_writeData16(x0);
	glcd_writeData16(x1);
}

//static void glcd_setY(uint16_t y0, uint16_t y1)
static void glcd_setY(volatile uint16_t y0, volatile uint16_t y1)
{
	glcd_writeCmd(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_writeData16(y0);
	glcd_writeData16(y1);
}

static void glcd_setXY(volatile uint16_t x0, volatile uint16_t x1, volatile uint16_t y0, volatile uint16_t y1)
{
	// kao set page u koji ces pisat
	if (glcd_orientation == P1)
	{
		glcd_setX(x0, x1);
		glcd_setY(y0, y1);
	}
	else if (glcd_orientation == P2)
	{
		glcd_setX(max_x-x1, max_x-x0);
		glcd_setY(max_y-y1, max_y-y0-1);	// da ne omasi za 1 pixel
	}
	else if (glcd_orientation == L1)
	{
		glcd_setX(y1, y0);
		glcd_setY(max_x-x1, max_x-x0);
	}
	else if (glcd_orientation == L2)
	{
		glcd_setX(max_y-y0, max_y-y1-1);	// da ne omasi za 1 pixel
		glcd_setY(x0, x1);
	}
	// nakon svakog setXY treba ovo
	glcd_writeCmd(ILI9341_CMD_MEMORY_WRITE);	
}


// javne funkcije

void glcd_pixel(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t color)
{
	glcd_setXY(x0,x0,y0,y0);
	glcd_writeData16(color);
}

void glcd_hline(volatile uint16_t x0, uint16_t y0, uint16_t length, uint16_t color)
{
	glcd_setXY(x0,x0+length,y0,y0);

	// sporija verzija
	// 79 ms
	/*
	for (int i=0; i<length; i++)
	{
		glcd_writeData16(color);
	}
	*/

	// brza verzija
	// ustedi na CS signalu
	// 53 ms
        glcd_dc_high();
        glcd_cs_low();
	for (int i=0; i<length; i++)
	{
		/*
		   // 53 ms
		spi_write(color >> 8);
		spi_write(color & 0xFF);
		*/
		// 51 ms
		//spi_write16(color);	// XXX povreda layera radi brzine
		spi_write16_fast(color);	// XXX povreda layera radi brzine

		// test
		/*
		spi_write_fast(color >> 8);	// XXX povreda layera radi brzine
		spi_write_fast(color & 0xFF);	// XXX povreda layera radi brzine
		*/
	}
        glcd_cs_high();
}

void glcd_hline2(volatile uint16_t x0, uint16_t y0, uint16_t length, uint16_t colors[])
{
	glcd_setXY(x0, x0+length, y0, y0);
	// INFO povreda layera radi brzine
	glcd_dc_high();
	glcd_cs_low();

	for (int i=0; i<length; i++)
	{
		spi_write16_fast(colors[i]);
	}

	glcd_cs_high();
}

		// ne toliko koristena funkcija
void glcd_vline(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color)
{
	if ((glcd_orientation == P1) || (glcd_orientation == P2))
	{
		glcd_setXY(x0,x0,y0,y0+length);
	}
	if ((glcd_orientation == L1) || (glcd_orientation == L2))
	{
		glcd_setXY(x0,x0,y0+length,y0);
	}
	//glcd_writeCmd(ILI9341_CMD_MEMORY_WRITE);

	// ustedi na CS signalu
        //glcd_dc_high();
        //glcd_cs_low();
	for (int i=0; i<length; i++)
	{
		glcd_writeData16(color);
		//spi_write16(color);
		//spi_write16_fast(color);
		/*
		spi_rw(color >> 8);
		spi_rw(color & 0xFF);
		*/
	}
        glcd_cs_high();
}

void glcd_fillRectangle(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t length, volatile uint16_t width, volatile uint16_t color)
{
	for (int i=0;i<width;i++)
	{
		glcd_hline(x0,y0+i,length,color);
	}
}

void glcd_bg(int color)
{
	//glcd_fillRectangle(0, 0, max_x, max_y, color);
	//glcd_fillRectangle(0, 0, 240, 320, color);
	glcd_fillRectangle(0, 0, 320, 320, color);
}

void glcd_char(unsigned char ascii, unsigned int x, unsigned int y, unsigned int size, unsigned int fgcolor)	
{
	if ( (ascii >= 32) || (ascii >= 126) )
	{
		for (int i=0; i<CHAR_X; i++)
		{
			//unsigned char temp = pgm_read_byte(&simpleFont[ascii-32][i]);	// because font.c starts at 0, not 32
			unsigned char temp = simpleFont[ascii-32][i];	// ARM

			for (int j=0; j<8; j++)
			{
				if ((temp >> j) & 1)	// ako bit na trenutacnoj pozici 1
				{
					// onda ga ispisi, pixel po pixel
					glcd_fillRectangle(x+i*size, y+j*size, size, size, fgcolor);
				}
				else
				{
					// bojaj u pozadinsku boju, "obrisi"
					glcd_fillRectangle(x+i*size, y+j*size, size, size, bgcolor);
				}
			}
		}
	}
	else if ((ascii != '\n') && (ascii != '\r'))
	{
		printf("Zajeb, glcd_char() dobio neprintabilni znak: (int) %d\n", ascii);
		// If not printable write red kocka
		glcd_fillRectangle(x, y, size*CHAR_X, size*CHAR_Y, red);
	}
}

//void glcd_string(char *string, unsigned int x, unsigned int y, unsigned int size, unsigned int fgcolor)
void glcd_string(char *string, volatile uint16_t x, volatile uint16_t y, uint8_t size, uint16_t fgcolor)
{
	while (*string)
	{
		// TODO
		// provjere da ne ispisuje prazno mjesto na pocetku linije
		// Kad dodje do kraja ekrana da novu liniju krene ispisiavat od pocetka i printfa upozorenje
		// Da ne razlomi rijec na sred nego citavu prebaci u novi red (vjerojatno ce znatno usporit)


		//if (x < max_x)
		{
			if ((*string == '\n') || (*string == '\r'))
			{
				// samo idi u novi red, bez ispisa
				x = 0;
				y += (CHAR_Y+CHAR_SPACE)*size;
				string++;
			}
			//else
			{

				if (x < max_x)
				{
					glcd_char(*string, x, y, size, fgcolor);
					string++;
					x += (CHAR_X+CHAR_SPACE)*size;	// pomakni kursor
				}
				else
				{
					x = 0;
					y += (CHAR_Y+CHAR_SPACE)*size;
				}
			}
		}
	}
}

uint8_t glcd_number(int32_t number, uint16_t x0, uint16_t y0, uint8_t size, uint16_t fgcolor)
{
	uint8_t char_buffer[10] = "";
	uint8_t i = 0;
	uint8_t digits_count = 0;

	if (number < 0)
	{
		// ako je negativni broj ispisi minus, pomjeri kursor i nastavi normalno
		digits_count = 1;
		glcd_char('-',x0, y0, size, fgcolor);
		number = -number;
		if (x0 < max_x)
			x0 += (CHAR_X+CHAR_SPACE)*size;
	}
	else if (number == 0)
	{
		digits_count = 1;
		glcd_char('0',x0, y0, size, fgcolor);
		if (x0 < max_x)
			x0 += (CHAR_X+CHAR_SPACE)*size;
		return digits_count;
	}
	
	while (number > 0)
	{
		char_buffer[i++] = number % 10;
		number /= 10;
	}

	digits_count += i;
	for (; i > 0; i--)
	{
		glcd_char('0'+ char_buffer[i - 1],x0, y0, size, fgcolor);
		if (x0 < max_x)
			x0 += (CHAR_X+CHAR_SPACE)*size;
	}
	return digits_count;
}

void glcd_set_bgcolor(uint16_t color)
{
	bgcolor = color;
}

uint16_t glcd_get_bgcolor()
{
	return bgcolor;
}

#define MY	7	
#define MX	6
#define MV	5	// vertical refresh
#define ML	4	// vertical refresh
#define BGR	3
#define MH	2

void glcd_init()
{
	// TODO provjera jel pozvat init prije poziva ostalih funkcija
	glcd_io_init();
	glcd_spi_init();
	glcd_led_on();
	glcd_ili9341_init();

	glcd_setOrientation(P1);
	glcd_set_bgcolor(black);
	//uint16_t bgcolor = glcd_get_bgcolor();
	glcd_bg(bgcolor);
}

void glcd_test()
{
	static uint8_t mod = 0;
	// provjerit sa raznim bojama pozadina TODO

	if (mod%2 == 0)
	{
		glcd_bg(white);
		glcd_set_bgcolor(white);
	}
	else
	{
		glcd_bg(black);
		glcd_set_bgcolor(black);
	}

	/*
	glcd_setOrientation(L2);
	glcd_string("Fuck you world", 0, 0, 2, blue);
	glcd_setOrientation(L1);
	glcd_string("Fuck you world", 0, 0, 2, yellow);
	glcd_setOrientation(P1);
	glcd_string("Fuck you world", 0, 0, 2, green);
	glcd_setOrientation(P2);
	glcd_string("Fuck you world", 0, 0, 2, red);
	*/

	glcd_writeCmd(0x36);		// memory access control
	// default
	//glcd_writeData( (0 << MY) | (1 << MX) | (0 << MV) | (1 << ML) | (1 << BGR) | (0 << MH) );

	/*
	   					osvjezava
	   0	MY=0 MX=0 MV=0 ML=0 MH=0	P1	P1m
	   1	MY=0 MX=0 MV=0 ML=0 MH=1	P1	P2
	   2	MY=0 MX=0 MV=0 ML=1 MH=0	P2	P1
	   3	MY=0 MX=0 MV=0 ML=1 MH=1	P1	P2m
	   4	MY=0 MX=0 MV=1 ML=0 MH=0	P2	L1
	   5	MY=0 MX=0 MV=1 ML=0 MH=1	L1	L1m
	   6	MY=0 MX=0 MV=1 ML=1 MH=0	L1	L2m
	   7	MY=0 MX=0 MV=1 ML=1 MH=1	L2	L2
	   8	MY=0 MX=1 MV=0 ML=0 MH=0	L2	P1m
	   9	MY=0 MX=1 MV=0 ML=0 MH=1	P1	P2
	   10	MY=0 MX=1 MV=0 ML=1 MH=0	P2	P1
	   11	MY=0 MX=1 MV=0 ML=1 MH=1	P1	P2m
	   12	MY=0 MX=1 MV=1 ML=0 MH=0	P2	L1
	   13	MY=0 MX=1 MV=1 ML=0 MH=1	L1	L1m
	   14	MY=0 MX=1 MV=1 ML=1 MH=0	L1	L2m
	   15	MY=0 MX=1 MV=1 ML=1 MH=1	L2	L2
	   16	MY=1 MX=0 MV=0 ML=0 MH=0	L2	P1m
	   17	MY=1 MX=0 MV=0 ML=0 MH=1	P1	P2
	   18	MY=1 MX=0 MV=0 ML=1 MH=0	P2	P1
	   19	MY=1 MX=0 MV=0 ML=1 MH=1	P1	P2m
	   20	MY=1 MX=0 MV=1 ML=0 MH=0	P2	L1
	   21	MY=1 MX=0 MV=1 ML=0 MH=1	L1	L1m
	   22	MY=1 MX=0 MV=1 ML=1 MH=0	L1	L2m
	   23	MY=1 MX=0 MV=1 ML=1 MH=1	L2	L2
	   24	MY=1 MX=1 MV=0 ML=0 MH=0	L2	P1m
	   25	MY=1 MX=1 MV=0 ML=0 MH=1	P1	P2
	   26	MY=1 MX=1 MV=0 ML=1 MH=0	P2	P1
	   27	MY=1 MX=1 MV=0 ML=1 MH=1	P1	P2m
	   28	MY=1 MX=1 MV=1 ML=0 MH=0	P2	L1
	   29	MY=1 MX=1 MV=1 ML=0 MH=1	L1	L1m
	   30	MY=1 MX=1 MV=1 ML=1 MH=0	L1	L2m
	   31	MY=1 MX=1 MV=1 ML=1 MH=1	L2	L2
	   */








	/*
	   					osvjezava
	   0	MY=0 MX=0 MV=0 ML=0 MH=0	P1	P1m

	   7	MY=0 MX=0 MV=1 ML=1 MH=1	L2	L2
	   31	MY=1 MX=1 MV=1 ML=1 MH=1	L2	L2
	   15	MY=0 MX=1 MV=1 ML=1 MH=1	L2	L2
	   23	MY=1 MX=0 MV=1 ML=1 MH=1	L2	L2

	   13	MY=0 MX=1 MV=1 ML=0 MH=1	L1	L1m
	   21	MY=1 MX=0 MV=1 ML=0 MH=1	L1	L1m
	   5	MY=0 MX=0 MV=1 ML=0 MH=1	L1	L1m
	   29	MY=1 MX=1 MV=1 ML=0 MH=1	L1	L1m




	   1	MY=0 MX=0 MV=0 ML=0 MH=1	P1	P2
	   2	MY=0 MX=0 MV=0 ML=1 MH=0	P2	P1



	   3	MY=0 MX=0 MV=0 ML=1 MH=1	P1	P2m
	   4	MY=0 MX=0 MV=1 ML=0 MH=0	P2	L1
	   6	MY=0 MX=0 MV=1 ML=1 MH=0	L1	L2m
	   8	MY=0 MX=1 MV=0 ML=0 MH=0	L2	P1m
	   9	MY=0 MX=1 MV=0 ML=0 MH=1	P1	P2
	   10	MY=0 MX=1 MV=0 ML=1 MH=0	P2	P1
	   11	MY=0 MX=1 MV=0 ML=1 MH=1	P1	P2m
	   12	MY=0 MX=1 MV=1 ML=0 MH=0	P2	L1
	   14	MY=0 MX=1 MV=1 ML=1 MH=0	L1	L2m
	   16	MY=1 MX=0 MV=0 ML=0 MH=0	L2	P1m
	   17	MY=1 MX=0 MV=0 ML=0 MH=1	P1	P2
	   18	MY=1 MX=0 MV=0 ML=1 MH=0	P2	P1
	   19	MY=1 MX=0 MV=0 ML=1 MH=1	P1	P2m
	   20	MY=1 MX=0 MV=1 ML=0 MH=0	P2	L1
	   22	MY=1 MX=0 MV=1 ML=1 MH=0	L1	L2m
	   24	MY=1 MX=1 MV=0 ML=0 MH=0	L2	P1m
	   25	MY=1 MX=1 MV=0 ML=0 MH=1	P1	P2
	   26	MY=1 MX=1 MV=0 ML=1 MH=0	P2	P1
	   27	MY=1 MX=1 MV=0 ML=1 MH=1	P1	P2m
	   28	MY=1 MX=1 MV=1 ML=0 MH=0	P2	L1
	   30	MY=1 MX=1 MV=1 ML=1 MH=0	L1	L2m
	   */
	
	uint8_t a[5] = {mod>>0&1, mod>>1&1, mod>>2&1, mod>>3&1, mod>>4&1};	// little endian
	printf("mod: %d %d%d%d%d%d\n",mod, a[4], a[3], a[2], a[1], a[0]);

	glcd_writeData( (a[0] << MY) | (a[1] << MX) | (a[2] << MV) | (a[3] << ML) | (1 << BGR) | (1 << MH) );

	glcd_string("Fuck you world", 0, 0, 2, blue);
	glcd_number(mod, 50,50,2,red);
	mod++;

}

void glcd_speedtest()
{
	glcd_setOrientation(P2);
	uint16_t t1 = get_uptime_ms();
	glcd_bg(black);
	uint16_t t2 = get_uptime_ms();

	printf("glcd_speedtest trajao: %lu ms\n", t2-t1);
	glcd_number(t2-t1, 50, 50, 3, red);
}


void glcd_img_test()
{
	glcd_setOrientation(P1);
	// XXX 240x320 bmp ne radi u landscapeu

	//glcd_setXY(0,max_x, 0, max_y);
	glcd_setXY(0,240, 0, 320);

        glcd_dc_high();
        glcd_cs_low();

	for (uint32_t i=0; i<240*320; i++)
	{
		//spi_write16_fast(bmp_data[i]);

	}
	glcd_cs_high();

	/*
	// spremi 240 bajtova
	uint16_t colors[240] = {};


	// sa ovima se dobije automatska orijentacija
	for (int y=0; y<320; y++)
	{
		for (int i=0; i<240; i++)
		{
			colors[i] = bmp_data[240*y+i];	// spremi 240 boja u array
		}
		glcd_hline2(0,y, max_x, colors);	// posalji citavu liniju
	}
	*/



	printf("%s() end\n", __func__);

}
