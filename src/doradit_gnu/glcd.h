

/**************************************************************************************************
*  					ILI9341							  *
**************************************************************************************************/
#ifdef ILI9341
#include "ili9341.h"
#include "ili9341cmd.h"
#include "ili9341.h"
#include "ili9341-init.c"

#define glcd_init()	glcd_ili9341_init()
#define glcd_io_init()	glcd_ili9341_io_init()
#define glcd_sendCmd(uint8_t data)	glcd_ili9341_sendCmd(uint8_t data)



/**************************************************************************************************
*  					ST7783							  *
**************************************************************************************************/
#elif defined ST7783
//#include "st7783.h"
#include "st7783.c"


// trebaju prototipovi zbog defineova ispod
void glcd_io_init();
void glcd_st7783_io_init();
void glcd_st7783_init();
void glcd_st7783_setXY(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);
void glcd_setXY(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);




#define glcd_io_init()		glcd_st7783_io_init()
#define glcd_init()		glcd_st7783_init()
//#define glcd_setXY(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)	glcd_st7783_setXY(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
#define glcd_setXY		glcd_st7783_setXY

#else
	printf("Zajeb, definiraj LCD\n");
#endif
