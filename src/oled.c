// created 141205
// radi na 5V

#include "oled.h"
#include <stdio.h>
#include "delay.h"
#include <stdbool.h>

#define SSD1306_LCDWIDTH	128
#define SSD1306_LCDHEIGHT	64
#define SSD1306_SETCONTRAST	0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 	0xA5
#define SSD1306_NORMALDISPLAY 	0xA6
#define SSD1306_INVERTDISPLAY 	0xA7
#define SSD1306_DISPLAYOFF 	0xAE
#define SSD1306_DISPLAYON 	0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 	0xDA
#define SSD1306_SETVCOMDETECT 	0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 	0xD9
#define SSD1306_SETMULTIPLEX 	0xA8
#define SSD1306_SETLOWCOLUMN 	0x00
#define SSD1306_SETHIGHCOLUMN 	0x10
#define SSD1306_SETSTARTLINE 	0x40
#define SSD1306_MEMORYMODE 	0x20
#define SSD1306_COLUMNADDR 	0x21
#define SSD1306_PAGEADDR   	0x22
#define SSD1306_COMSCANINC 	0xC0
#define SSD1306_COMSCANDEC 	0xC8
#define SSD1306_SEGREMAP	0xA0
#define SSD1306_CHARGEPUMP	0x8D
#define SSD1306_EXTERNALVCC	0x1
#define SSD1306_SWITCHCAPVCC	0x2

#define SSD1306_CMD		0x00	// djeluje da bilo sta moze bit ovdje, pa i druga komanda
//c#define SSD1306_CMD		0x22
//#define SSD1306_DATA		0x40
#define SSD1306_DATA		0x40	// i ovo moze bit bilo sta

uint8_t a[] = {0b01001100, 0b10010010, 0b10010010, 0b10010010, 0b01111110};

void ssd1306_command(uint8_t cmd)
{
	i2c_start(2);
	i2c_write(2, OLED_ADDR_W);
	i2c_write(2, SSD1306_CMD);
	i2c_write(2, cmd);
	i2c_stop(2);
}

// ne koristi nista ovu funkciju
void  ssd1306_data(uint8_t cmd)
{
	i2c_start(2);
	i2c_write(2, OLED_ADDR_W);
	i2c_write(2, SSD1306_DATA);
	i2c_write(2, cmd);
	i2c_stop(2);
}

void oled_io_init(void)
{
	printf("oled_io_init pocetak\n");
	//i2c_init(2, 100000);
	//i2c_init(2, 400000);
	//i2c_init(2, 800000);
	i2c_init(2, 1000000);

	printf("oled_io_init kraj\n");
}

void ssd1306_setXY(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	if (x1<128)
	{
		//ssd1306_command(0x21);	// column
		//ssd1306_command(0x71);	// column
		ssd1306_command(x0);
		ssd1306_command(x1);
	}
	else
	{
		printf("ssd1306_setXY(): x1 larger than 128\n");
	}
	if (y1<64)
	{
		ssd1306_command(0x22);	// row
		ssd1306_command(y0);
		ssd1306_command(y1);
	}
	else
	{
		printf("ssd1306_setXY(): y1 larger than 64\n");
	}
}

void ssd1306_fillRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color)
{
	//ssd1306_setXY(x0, y0, x1, y1);

	i2c_start(2);
	i2c_write(2, OLED_ADDR_W);
	i2c_write(2, SSD1306_DATA);

	// koliko pixela treba obojat
	uint16_t count = (x1 - x0) * (y1 - y0) /8;
	printf("ssd1306_fillRectangle(): count: %d\n", count);

	for (uint8_t i=0; i<count ; i++)
	{
		if (color)
		{
			i2c_write(2, 0xFF);
		}
		else
		{
			i2c_write(2, 0x00);
		}
	}

	i2c_stop(2);
}

void crtaj_a(void)
{
	//uint8_t t = 
}

void ssd1306_bg(bool arg)
{
	ssd1306_setXY(0, 0, 127, 63);

	i2c_start(2);
	i2c_write(2, OLED_ADDR_W);
	i2c_write(2, SSD1306_DATA);

	for (uint16_t i=0; i<128*64/8; i++)
	{
		if (arg)
		{
			i2c_write(2, 0xFF);
		}
		else
		{
			i2c_write(2, 0x00);
		}
	}
	i2c_stop(2);
}

uint32_t oled_init()
{
	printf("oled_init() pocetak\n");
	//printf("DEBUG\t\t\t\tDEBUG\n");

	// Init sequence for 128x64 OLED module
	ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
	ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
	ssd1306_command(0x80);                			// the suggested ratio 0x80
	ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
	ssd1306_command(0x3F);
	ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
	ssd1306_command(0x0);                                   // no offset
	ssd1306_command(SSD1306_SETSTARTLINE);// | 0x0);        // line #0
	ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
	ssd1306_command(0x14); 					// using internal VCC
	ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
	ssd1306_command(0x00);					// 0x00 horizontal addressing
	ssd1306_command(SSD1306_SEGREMAP | 0x1);		// rotate screen 180
	ssd1306_command(SSD1306_COMSCANDEC);			// rotate screen 180
	ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
	ssd1306_command(0x12);
	ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
	ssd1306_command(0xCF);
	ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
	ssd1306_command(0xF1);
	ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
	ssd1306_command(0x40);
	ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
	ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
	ssd1306_command(SSD1306_DISPLAYON);                     //switch on OLED

	printf("oled_init() kraj\n");

	ssd1306_bg(0);
	//ssd1306_bg(1);
	//ssd1306_bg(0);
	//ssd1306_fillRectangle(30,30,50,50,0);

	return 0;
}

void oled_kocka()
{
	/*
	ssd1306_fillRectangle(0,0,10,10,0);
	delay_ms(50);
	ssd1306_fillRectangle(10,0,20,10,0);
	*/

	// kockica 8x8 pixela

	/*
	for (int i=0; i<12; i++)
	{
		//ssd1306_fillRectangle(0,0,8,8, 1);
		ssd1306_fillRectangle(i,0,i+8,8, 1);
	}
	*/
}

void oled_example(void)
{
	oled_io_init();
	oled_init();

	ssd1306_bg(0);
	delay_ms(500);
	ssd1306_bg(1);
}
