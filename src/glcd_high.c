#include "glcd_high.h"
//#include "src/img.bmp.c"

// 150116	vraceno na "sporije" verzije, ali se postuje layerizacija
//		"brze" verzije dobiju max 1 ms na -O2 ili -O3 (jednako brzo radi);

//static unsigned int max_x, max_y;
//static unsigned int bgcolor = black;
//static unsigned char glcd_orientation;
static uint16_t max_x, max_y;
static uint16_t bgcolor = black;	// for 16b LCD
static uint8_t glcd_orientation;

int8_t glcd_set_orientation(uint8_t orientation)
{
	if (glcd_set_hw_orientation(orientation) != 0)	// vratio je nesto u slucaju errora
	{
		printf("%s(): Wrong GLCD orientation: %d\n", __func__, orientation);
		return -1;
	}
	else
	{
		glcd_orientation = orientation;

		if ((glcd_orientation == P1) || (glcd_orientation == P1m) || (glcd_orientation == P2) || (glcd_orientation == P2m))
		{
			max_x = 239;
			max_y = 319;
		}

		else if ((glcd_orientation == L1) || (glcd_orientation == L1m) || (glcd_orientation == L2) || (glcd_orientation == L2m))
		{
			max_x = 319;
			max_y = 239;
		}
	}
	return 0;
}

int16_t glcd_get_width()
{
	return max_x;
}

int16_t glcd_get_height()
{
	return max_y;
}

const char *glcd_get_orientation_string()
{
	uint8_t orientation = glcd_get_orientation();

	switch (orientation)
	{
		case 0:
			return "P1m";
			break;
		case 1:
			return "L1";
			break;
		case 2:
			return "P1";
			break;
		case 3:
			return "L2m";
			break;
		case 4:
			return "P2";
			break;
		case 5:
			return "L1m";
			break;
		case 6:
			return "P2m";
			break;
		case 7:
			return "L2";
			break;
		default:
			return "error";
			break;

	}
}

/*
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
*/

static void glcd_setXY(volatile uint16_t x0, volatile uint16_t x1, volatile uint16_t y0, volatile uint16_t y1)
{
	// kao set page u koji ces pisat
	// imamo hw orijentacije, nema vise racunanja ovdje
	// set X
	glcd_writeCmd(ILI9341_CMD_COLUMN_ADDRESS_SET);

	glcd_writeData16(x0);
	glcd_writeData16(x1);

	// set Y
	glcd_writeCmd(ILI9341_CMD_PAGE_ADDRESS_SET);
	glcd_writeData16(y0);
	glcd_writeData16(y1);

	// engage
	glcd_writeCmd(ILI9341_CMD_MEMORY_WRITE);	
	// TODO presaltat ovo direktno na SPI funkcije pa izmjerit brzinu

	//printf("%s(): x0: %d, x1: %d, y0: %d y1: %d\n", __func__, x0, x1, y0, y1);
}


void glcd_pixel(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t color)
{
	glcd_setXY(x0,x0,y0,y0);
	glcd_writeData16(color);
}

void glcd_hline(volatile uint16_t x0, uint16_t y0, uint16_t length, uint16_t color)
{
	// XXX sjebe kad printa plavu boju
	//glcd_setXY(x0,x0+length+1,y0,y0);	// +1 jer je duzina, ne koordinata
	glcd_setXY(x0,x0+length,y0,y0);	

	// sporija verzija
	// 79 ms
	/*
	for (int i=0; i<=length; i++)
	{
		glcd_writeData16(color);
	}
	*/

	// brza verzija
	// ustedi na CS signalu
	// 53 ms
	glcd_dc_high();
	glcd_cs_low();
	for (int i=0; i<=length; i++)
	{
		spi_write16_fast(color);	// INFO povreda layera radi brzine
	}
	glcd_cs_high();
}

		// ne toliko koristena funkcija
void glcd_vline(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color)
{
	glcd_setXY(x0,x0,y0,y0+length+1);	// +1 jer je duzina, a ne koordinata

	// ustedi na CS signalu
	//glcd_dc_high();
	//glcd_cs_low();
	for (int i=0; i<length+1; i++)
	{
		glcd_writeData16(color);
		//spi_write16_fast(color);
	}
	//glcd_cs_high();
}

//void glcd_fillRectangle(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t length, volatile uint16_t width, volatile uint16_t color)
void glcd_fillRectangle(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t width, volatile uint16_t height, volatile uint16_t color)
{
	// TODO provjerit, moguce da ne nacrta liniju u 0,0 ili mi se mozda samo cini
	for (uint16_t i=0; i<=height; i++)
	{
		glcd_hline(x0,y0+i, width,color);
	}
}

void glcd_bg(int color)
{
	//glcd_fillRectangle(0, 0, max_x, max_y, color);
	//glcd_fillRectangle(0, 0, 240, 320, color);
	bgcolor = color;
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

void glcd_string(const char *string, volatile uint16_t x, volatile uint16_t y, uint8_t size, uint16_t fgcolor)
{
	while (*string)
	{
		// TODO
		// provjere da ne ispisuje prazno mjesto na pocetku linije
		// Kad dodje do kraja ekrana da novu liniju krene ispisiavat od pocetka i printfa upozorenje
		// Da ne razlomi rijec na sred nego citavu prebaci u novi red (vjerojatno ce znatno usporit)





		// 2015.
		// XXX razjebe ga kad dobije \n
		// ako je string dugacak dobro ga ispise u novom redu, ali ne ako ima \n


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

uint8_t glcd_get_orientation()
{
	return glcd_orientation;
}

void glcd_init()
{
	// TODO provjera jel pozvat init prije poziva ostalih funkcija
	glcd_io_init();
	glcd_spi_init();
	glcd_led_on();
	glcd_ili9341_init();

	//glcd_set_bgcolor(black);
	//uint16_t bgcolor = glcd_get_bgcolor();
	glcd_bg(bgcolor);
}

void glcd_speedtest()
{
	//glcd_set_orientation(P2);
	uint16_t t1 = get_uptime_ms();
	glcd_bg(black);
	uint16_t t2 = get_uptime_ms();

	printf("glcd_speedtest trajao: %lu ms\n", t2-t1);
	glcd_number(t2-t1, 50, 50, 3, red);
}


void glcd_img_test()
{
	//glcd_set_orientation(P1);
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

void glcd_test()
{
	glcd_bg(bgcolor);
	static int i=0;

	if (glcd_set_orientation(i++) == 0)
	{
		glcd_string("Fuck you world.123.", 10, 10, 2, red);
		glcd_number(glcd_get_orientation(), 50,30,2,blue);
	}

}

void glcd_orientation_test()
{
	glcd_bg(bgcolor);
	glcd_set_orientation(P1);
	glcd_string("Fuck you world.", 0, 0, 2, red);
	glcd_set_orientation(P1m);
	glcd_string("Fuck you world.", 0, 20, 2, blue);
	glcd_set_orientation(L1);
	glcd_string("Fuck you world.", 0, 0, 2, yellow);
	glcd_set_orientation(L1m);
	glcd_string("Fuck you world.", 0, 20, 2, cyan);
}
