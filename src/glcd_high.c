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

			// TODO kako ce primatelj znat koliko je dugacak char?
			// mozda bolje samo vratit adresu
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

//static void glcd_setXY(volatile uint16_t x0, volatile uint16_t x1, volatile uint16_t y0, volatile uint16_t y1)
void glcd_setXY(volatile uint16_t x0, volatile uint16_t x1, volatile uint16_t y0, volatile uint16_t y1)
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
void glcd_fillRectangle(volatile uint16_t x0, volatile uint16_t y0, volatile uint16_t length, volatile uint16_t height, volatile uint16_t color)
{
	// TODO provjerit, moguce da ne nacrta liniju u 0,0 ili mi se mozda samo cini
	for (uint16_t i=0; i<=height; i++)
	{
		glcd_hline(x0,y0+i, length,color);
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

void glcd_clear_line(volatile uint16_t x, volatile uint16_t y, uint8_t size)
{
	glcd_fillRectangle(x, y, max_x, (CHAR_Y+CHAR_SPACE)*size, bgcolor);
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

//uint16_t tmp_buffer[] = {red, green, blue};
uint16_t tmp_buffer[] = {0x1FF1, 0xF1F1, blue};

void glcd_img_test()
{
	/*
	// patch da slika ispadne dobro
	glcd_set_orientation(P2m);	// za P1 mod

	glcd_setXY(0,240, 0, 320);
	glcd_dc_high();
	glcd_cs_low();

	for (uint32_t i=0; i<240*320; i++)
	{
		spi_write16_fast(bmp_data[i]);
	}
	glcd_cs_high();
	*/

	extern int dma_counter;

	static int printed=0;
	glcd_set_orientation(P1);

	//if (dma_counter < 4)
	//if (dma_counter > 0)
	{

#define SPI_PORT_TX_DMA_STREAM             DMA2_Stream3

		//printf("%s(): dma_counter: %d\n", __func__, dma_counter);
		//printf("%s(): dma_counter: %d TCIF: %d\n", __func__, dma_counter, DMA_GetITStatus(SPI_PORT_TX_DMA_STREAM, DMA_IT_TCIF3));

		//glcd_setXY(0,240, dma_counter*100, dma_counter*100+100);
		//glcd_setXY(40,200, 200, 260);
		glcd_setXY(0,240, 0, 320);

		glcd_dc_high();
		glcd_cs_low();
		//delay_ms(10);

		// samo omoguci DMA
		DMA_Cmd(DMA2_Stream3, ENABLE);
		//dma_counter++;

		//glcd_write_dma(&tmp_buffer[2], 65535);
		//glcd_write_dma((uint16_t *)red, 500);
	}
	if (printed == 0)
	{

		printf("%s(): odradio svoje\n", __func__);
		printed = 1;
	}


	/*
	uint32_t length = sizeof(bmp_data)/2;	// jer saljemo 2 bajta odjednom

	//for (uint32_t i=0; i<240*320; i++)
	while (length > 0)	// ovo radi u slucaju da je slika odrezana
	{
		//spi_write16_fast(bmp_data[i]);
		static int counter;
		spi_write16_fast(bmp_data[counter++]);
		length--;
	}
	*/
		//glcd_write_dma(bmp_data, 240*160);	// radi donekle, sjebane boje, manji dio slike tek
		//glcd_write_dma((uint16_t *)bmp_data, 240*160);
		//glcd_write_dma((uint16_t *)bmp_data, 64000);
		//glcd_write_dma((uint32_t *)bmp_data, 65000);	// nece isprintat vise od 65k

		// nova slika
		//glcd_write_dma((uint32_t *)bmp_data, 240*320);
		//glcd_write_dma(&bmp_data[0], 240*320*8);
		//glcd_write_dma(bmp_data, 240*320*8*2);


	//printf("%s() end\n", __func__);

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

void glcd_title(char *string, unsigned int size, unsigned int fgcolor, unsigned int bgcolor)
{
	//unsigned int x0 = max_x/2 - (strlen(string)*size*FONT_SPACE)/2;
	unsigned int x0 = max_x/2 - (strlen(string)*size*(CHAR_X + CHAR_SPACE))/2;
	//unsigned int y0 = 0.5*size*FONT_SPACE;
	unsigned int y0 = 0.5*size*(CHAR_X + CHAR_SPACE);
	//glcd_fillRectangle(0,0,max_x,2*size*FONT_SPACE,bgcolor);	// treperi
	glcd_fillRectangle(0, 0, max_x, 2*size*(CHAR_X + CHAR_SPACE), bgcolor);
	uint16_t old_bgcolor = glcd_get_bgcolor();
	glcd_set_bgcolor(bgcolor);
	glcd_string(string,x0,y0,size,fgcolor);
	glcd_set_bgcolor(old_bgcolor);
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

/*
void glcd_bar(unsigned int x0, unsigned int y0, unsigned int howmany, unsigned int bar_max, unsigned int size, unsigned int fgcolor, unsigned int rectangle_color)
{
	glcd_rectangle(x0, y0-size, FONT_SPACE*size*bar_max+size, FONT_Y*size+2*size-1, red);
	glcd_kocka(x0, y0, howmany, size, fgcolor);
}
*/

/*
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

/*
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
*/

/*
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
*/

/*
   
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
*/

/*
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
*/

/*
void glcd_rectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color)
{
	glcd_hline(x0, y0, length, color);
	glcd_hline(x0, y0+width, length, color);
	glcd_vline(x0, y0, width, color);
	glcd_vline(x0+length, y0, width, color);
}
*/

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

/*
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
*/
