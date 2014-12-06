/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <propaliidealist@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Johnny Sorocil
 * ----------------------------------------------------------------------------
 */

#include <stdint.h>
#include <stdlib.h>	// abs()
#include <string.h>	// strlen()
#include "glcd_ili9341-cmd.h"
#include "glcd_font.c"
//#include "glcd.h"
#include "glcd_ili9341-init.c"


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




/*
//void glcd_rectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color)
void glcd_rectangle(vuint16_t x0, vuint16_t y0, vuint16_t length, vuint16_t width, vuint16_t color)
{
	glcd_hline(x0, y0, length, color);
	glcd_hline(x0, y0+width, length, color);
	glcd_vline(x0, y0, width, color);
	glcd_vline(x0+length, y0, width, color);
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
void glcd_clr(unsigned int x0, unsigned int y0, unsigned int size) 
{
	//glcd_fillRectangle(x0, y0, size*10, size*10, bgcolor);
	glcd_fillRectangle(x0, y0, size*8, size*8, bgcolor);
}

void glcd_clrLine(unsigned int y0, unsigned int size)
{
	glcd_fillRectangle(0, y0-size, max_x, size*10, bgcolor);
}
*/

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

uint16_t glcd_color(uint8_t arg_red, uint8_t arg_green, uint8_t arg_blue)
{
	uint16_t rgb565;
	// primi RGB u postotcima i vrati nazad RGB565

	arg_red = arg_red*0.31; 	// 5b
	arg_blue = arg_blue*0.63; 	// 6b
	arg_green = arg_green*0.31; 	// 5b

	rgb565 = (arg_red << 11) + (arg_blue << 5) + arg_green;

	return rgb565;
}

void glcd_test_colors()
{
	for(int i=0; i<10; i++)
	{
		glcd_fillRectangle(i*20,0,50,  20,glcd_color(i*10,0,0));
		glcd_fillRectangle(i*20,20,50, 20,glcd_color(0,i*10,0));
		glcd_fillRectangle(i*20,40,50, 20,glcd_color(0,0,i*10));

		glcd_fillRectangle(i*20,60,50,  20,glcd_color(i*10,i*10,0));
		glcd_fillRectangle(i*20,80,50,  20,glcd_color(i*10,0,i*10));
		glcd_fillRectangle(i*20,100,50,  20,glcd_color(0,i*10,i*10));

		glcd_fillRectangle(i*20,120,50,  20,glcd_color(i*10,i*10,i*10));
	}
}
*/

void glcd_test_speed()
{
	// TODO treba mu RTC

	//uint32_t a,b;

	//a = get_uptime();
	//glcd_kockice(50, white, black);
	glcd_bg(black);
	//b = get_uptime();
	//printf("glcd_bg() time: %lu ms\n", b-a);

	/*
	uint32_t result = b-a;
	char sresult[33];		// TODO ispitat zasto radi i kad je [1]
					// XXX neki dio ovdje se ne slaze sa joystick-om
	sprintf(sresult, "%lu ms", result);
	*/

	//glcd_string(sresult, 50, 50, 4, red);
	//glcd_number(b-a, 50, 50, 4, blue);
}

/*
uint8_t kocka_flag;
uint16_t gposX, gposY;

void kocka(uint16_t size, int color, char direction)
{
	// TODO treba mu joystick
	static int16_t posX, posY;

	// omoguci postavljanje pocetne pozicije negdje drugdje osim 0,0
	if(kocka_flag == 0)
	{
		// prvo pozivanje
		posX = gposX;
		posY = gposY;

		kocka_flag = 1;
	}

	bgcolor = green;

	// obrisi staru
	glcd_fillRectangle(posX, posY, size, size, bgcolor);

	if(direction == 'd')
		posY += size;
	else if(direction == 'u')
		posY -= size;
	else if(direction == 'r')
		posX += size;
	else if(direction == 'l')
		posX -= size;
	else if(direction == 'x')	// joystick je stisnit
		//glcd_bg(bgcolor);
		glcd_bg(black);
	else if(direction == 'o')	// joystick miruje
		;
	else
		printf("krivi smjer\n");

	// provjere
	if(posX < 0)
		posX = max_x-10;	// da ne nacrta samo jedan pixel uz rub
	if(posY < 0)
		posY = max_y-10;	// da ne nacrta samo jedan pixel uz rub
	if(posX > max_x)
		posX = 0;
	if(posY > max_y)
		posY = 0;

	// napravi novu
	glcd_fillRectangle(posX, posY, size, size, color);

	//printf("x: %d y: %d\n", posX, posY);
}
*/
